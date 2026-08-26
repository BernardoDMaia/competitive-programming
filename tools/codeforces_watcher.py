from __future__ import annotations

import json
import os
import shutil
import subprocess
import time
import urllib.error
import urllib.parse
import urllib.request
from datetime import datetime, timedelta, timezone
from pathlib import Path

from archive_solution import load_config
from finish_current_problem import (
    ROOT,
    choose_nonconflicting_destination,
    codeforces_info,
    detect_destination,
    git_commit_move,
    move_cph_metadata,
    normalize_path,
)

STATE_FILE = ROOT / ".cp-watcher-state.json"
LOCK_FILE = ROOT / ".cp-codeforces-watcher.lock"
POLL_SECONDS = 45
PUSH_RETRY_SECONDS = 15 * 60


def run(*args: str) -> subprocess.CompletedProcess:
    return subprocess.run(args, cwd=ROOT, check=True, text=True, capture_output=True)


def load_state() -> dict:
    if not STATE_FILE.is_file():
        return {}
    try:
        return json.loads(STATE_FILE.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}


def save_state(state: dict) -> None:
    STATE_FILE.write_text(json.dumps(state, indent=2) + "\n", encoding="utf-8")


def parse_dt(value: str | None) -> datetime | None:
    if not value:
        return None
    try:
        return datetime.fromisoformat(value)
    except ValueError:
        return None


def pid_is_running(pid: int) -> bool:
    if pid <= 0:
        return False
    try:
        if os.name == "nt":
            result = subprocess.run(
                ["tasklist", "/FI", f"PID eq {pid}", "/NH"],
                check=False,
                text=True,
                capture_output=True,
            )
            return str(pid) in result.stdout
        os.kill(pid, 0)
        return True
    except Exception:
        return False


def acquire_lock() -> None:
    if LOCK_FILE.is_file():
        try:
            old_pid = int(LOCK_FILE.read_text(encoding="utf-8").strip())
        except (OSError, ValueError):
            old_pid = -1
        if pid_is_running(old_pid):
            raise SystemExit(f"Codeforces watcher is already running (PID {old_pid}).")
    LOCK_FILE.write_text(str(os.getpid()), encoding="utf-8")


def release_lock() -> None:
    try:
        if LOCK_FILE.is_file() and LOCK_FILE.read_text(encoding="utf-8").strip() == str(os.getpid()):
            LOCK_FILE.unlink()
    except OSError:
        pass


def fetch_accepted(handle: str) -> dict[tuple[int, str], datetime]:
    params = urllib.parse.urlencode({"handle": handle, "from": 1, "count": 1000})
    url = f"https://codeforces.com/api/user.status?{params}"
    with urllib.request.urlopen(url, timeout=15) as response:
        data = json.load(response)

    if data.get("status") != "OK":
        raise RuntimeError("Codeforces returned a non-OK response")

    accepted: dict[tuple[int, str], datetime] = {}
    for submission in data.get("result", []):
        if submission.get("verdict") != "OK":
            continue
        problem = submission.get("problem", {})
        contest_id = problem.get("contestId")
        index = str(problem.get("index", "")).upper()
        timestamp = submission.get("creationTimeSeconds")
        if contest_id is None or not index or not timestamp:
            continue
        key = (int(contest_id), index)
        when = datetime.fromtimestamp(int(timestamp), tz=timezone.utc)
        if key not in accepted or when < accepted[key]:
            accepted[key] = when
    return accepted


def git_path_has_changes(path: Path) -> bool:
    try:
        relative = path.resolve().relative_to(ROOT.resolve())
    except ValueError:
        return False
    result = subprocess.run(
        ["git", "status", "--porcelain", "--", str(relative)],
        cwd=ROOT,
        check=False,
        text=True,
        capture_output=True,
    )
    return bool(result.stdout.strip())


def iter_pending_codeforces() -> list[tuple[Path, Path, dict, tuple[int, str]]]:
    pending: list[tuple[Path, Path, dict, tuple[int, str]]] = []
    seen_sources: set[str] = set()

    for prob_path in ROOT.rglob("*.prob"):
        try:
            metadata = json.loads(prob_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            continue

        source_raw = str(metadata.get("srcPath", "")).strip()
        url = str(metadata.get("url", "")).strip()
        cf = codeforces_info(url)
        if not source_raw or cf is None:
            continue

        source = Path(source_raw).expanduser()
        try:
            source = source.resolve()
        except OSError:
            continue
        if not source.is_file():
            continue

        key = normalize_path(source)
        if key in seen_sources:
            continue
        seen_sources.add(key)

        _, _, destination = detect_destination(metadata, source)
        if normalize_path(source) == normalize_path(destination):
            # Normally this means the problem was already archived. If the
            # previous run moved it but Git commit failed, however, the final
            # file is still untracked/dirty. Keep it pending so the watcher can
            # repair the missing commit automatically.
            if not git_path_has_changes(source):
                continue

        pending.append((source, prob_path, metadata, cf))

    return pending


def archive_accepted(source: Path, prob_path: Path, metadata: dict, accepted_at: datetime) -> None:
    platform, problem_label, destination = detect_destination(metadata, source)
    if platform != "Codeforces":
        return

    message = f"solve(codeforces): {problem_label}"

    # Self-heal an interrupted previous archive: the source may already be at
    # the final path while still being untracked because staging/commit failed.
    if normalize_path(source) == normalize_path(destination):
        if git_path_has_changes(destination):
            if git_commit_move(source, destination, message, accepted_at):
                print(
                    f"[{datetime.now().astimezone().strftime('%H:%M:%S')}] "
                    f"Recovered missing commit -> {destination.relative_to(ROOT)} | {message}",
                    flush=True,
                )
        return

    destination, already_same = choose_nonconflicting_destination(destination, source)
    if already_same:
        if normalize_path(source) != normalize_path(destination):
            source.unlink()
            move_cph_metadata(metadata, prob_path, destination)
        return

    destination.parent.mkdir(parents=True, exist_ok=True)
    original_source = source
    if normalize_path(source) != normalize_path(destination):
        shutil.move(str(source), str(destination))
    else:
        destination = source

    move_cph_metadata(metadata, prob_path, destination)

    if git_commit_move(original_source, destination, message, accepted_at):
        print(
            f"[{datetime.now().astimezone().strftime('%H:%M:%S')}] "
            f"Accepted detected -> {destination.relative_to(ROOT)} | {message}",
            flush=True,
        )
    else:
        print(f"No commit created for {problem_label}; it may already be tracked.", flush=True)


def most_recent_schedule(now: datetime, weekday: int, hour: int, minute: int) -> datetime:
    days_back = (now.weekday() - weekday) % 7
    scheduled = (now - timedelta(days=days_back)).replace(
        hour=hour, minute=minute, second=0, microsecond=0
    )
    if scheduled > now:
        scheduled -= timedelta(days=7)
    return scheduled


def maybe_weekly_push(config: dict, state: dict) -> None:
    weekly = config.get("weekly_push", {})
    if not isinstance(weekly, dict) or not weekly.get("enabled"):
        return

    try:
        weekday = int(weekly.get("weekday", 6))
        hour = int(weekly.get("hour", 20))
        minute = int(weekly.get("minute", 0))
    except (TypeError, ValueError):
        return

    now = datetime.now().astimezone()
    scheduled = most_recent_schedule(now, weekday, hour, minute)
    last_success = parse_dt(state.get("last_weekly_push"))
    if last_success is not None and last_success.astimezone() >= scheduled:
        return

    last_attempt = parse_dt(state.get("last_weekly_push_attempt"))
    if last_attempt is not None and (now - last_attempt.astimezone()).total_seconds() < PUSH_RETRY_SECONDS:
        return

    state["last_weekly_push_attempt"] = now.isoformat()
    save_state(state)

    try:
        branch = run("git", "branch", "--show-current").stdout.strip()
        if branch != "main":
            print(f"Weekly push postponed: current branch is '{branch}', not main.", flush=True)
            return

        run("git", "fetch", "origin", "main")
        behind = int(run("git", "rev-list", "--count", "HEAD..origin/main").stdout.strip() or "0")
        if behind:
            print(
                f"Weekly push postponed: local main is behind origin/main by {behind} commit(s).",
                flush=True,
            )
            return

        pending = int(run("git", "rev-list", "--count", "origin/main..HEAD").stdout.strip() or "0")
        if pending:
            subprocess.run(["git", "push", "origin", "main"], cwd=ROOT, check=True)
            print(f"Weekly push completed: {pending} commit(s) published.", flush=True)
        else:
            print("Weekly push check: no pending commits.", flush=True)

        state["last_weekly_push"] = now.isoformat()
        save_state(state)
    except subprocess.CalledProcessError as exc:
        print(f"Weekly push failed and will be retried later: {exc}", flush=True)


def main() -> None:
    config = load_config()
    handle = str(config.get("codeforces_handle", "")).strip()
    if not handle:
        raise SystemExit(
            "Codeforces handle is not configured. Run the VS Code task "
            "'CP: Configure Codeforces handle' once."
        )

    acquire_lock()
    state = load_state()
    print(f"Codeforces Accepted watcher started for {handle}.", flush=True)
    print(f"Polling every {POLL_SECONDS} seconds. Accepted solutions are committed locally.", flush=True)

    try:
        while True:
            config = load_config()
            handle = str(config.get("codeforces_handle", handle)).strip() or handle

            try:
                pending = iter_pending_codeforces()
                if pending:
                    accepted = fetch_accepted(handle)
                    for source, prob_path, metadata, cf in pending:
                        accepted_at = accepted.get(cf)
                        if accepted_at is not None:
                            archive_accepted(source, prob_path, metadata, accepted_at)
            except urllib.error.URLError as exc:
                print(f"Codeforces API temporarily unavailable: {exc}", flush=True)
            except Exception as exc:
                print(f"Watcher warning: {exc}", flush=True)

            try:
                maybe_weekly_push(config, state)
            except Exception as exc:
                print(f"Weekly push warning: {exc}", flush=True)

            time.sleep(POLL_SECONDS)
    except KeyboardInterrupt:
        print("Codeforces watcher stopped.")
    finally:
        release_lock()


if __name__ == "__main__":
    main()
