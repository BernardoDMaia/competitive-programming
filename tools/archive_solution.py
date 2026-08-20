from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import sys
import urllib.parse
import urllib.request
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = ROOT / ".cpconfig.json"

PLATFORMS = {
    "codeforces": "Codeforces",
    "cf": "Codeforces",
    "cses": "CSES",
    "usaco": "USACO",
    "obi": "OBI",
    "atcoder": "AtCoder",
    "beecrowd": "Beecrowd",
    "icpc": "ICPC",
}


def run(*args: str, env: dict[str, str] | None = None) -> subprocess.CompletedProcess:
    return subprocess.run(args, cwd=ROOT, check=True, env=env)


def load_config() -> dict:
    config: dict = {}
    if CONFIG_FILE.is_file():
        try:
            config = json.loads(CONFIG_FILE.read_text(encoding="utf-8"))
        except (json.JSONDecodeError, OSError):
            pass

    env_handle = os.getenv("CODEFORCES_HANDLE", "").strip()
    if env_handle:
        config["codeforces_handle"] = env_handle
    return config


def normalize_platform(raw: str) -> str:
    key = raw.strip().lower()
    return PLATFORMS.get(key, raw.strip() or "Uncategorized")


def parse_codeforces_problem_id(problem_id: str) -> tuple[int, str] | None:
    match = re.fullmatch(r"(\d+)([A-Za-z][A-Za-z0-9]*)", problem_id.strip())
    if not match:
        return None
    return int(match.group(1)), match.group(2).upper()


def codeforces_accepted(handle: str, problem_id: str) -> tuple[bool, datetime | None]:
    parsed = parse_codeforces_problem_id(problem_id)
    if not parsed:
        return False, None

    contest_id, index = parsed
    params = urllib.parse.urlencode({"handle": handle, "from": 1, "count": 1000})
    url = f"https://codeforces.com/api/user.status?{params}"

    try:
        with urllib.request.urlopen(url, timeout=10) as response:
            data = json.load(response)
    except Exception as exc:
        print(f"Warning: could not verify Codeforces submission: {exc}")
        return False, None

    if data.get("status") != "OK":
        return False, None

    matches = []
    for submission in data.get("result", []):
        problem = submission.get("problem", {})
        if (
            submission.get("verdict") == "OK"
            and problem.get("contestId") == contest_id
            and str(problem.get("index", "")).upper() == index
        ):
            matches.append(submission)

    if not matches:
        return False, None

    # Use the first Accepted chronologically for an honest training history.
    accepted = min(matches, key=lambda item: item.get("creationTimeSeconds", 0))
    timestamp = accepted.get("creationTimeSeconds")
    if not timestamp:
        return True, None

    return True, datetime.fromtimestamp(timestamp, tz=timezone.utc)


def choose_destination(platform: str, problem_id: str, source: Path) -> Path:
    if platform == "USACO":
        contest = input("Contest folder (e.g. 2016-January-Gold): ").strip()
        folder = ROOT / platform / (contest or "Uncategorized")
    elif platform == "Codeforces":
        parsed = parse_codeforces_problem_id(problem_id)
        folder = ROOT / platform / (str(parsed[0]) if parsed else "Uncategorized")
    else:
        folder = ROOT / platform

    folder.mkdir(parents=True, exist_ok=True)

    safe_name = source.name
    if problem_id and source.stem.lower() in {"main", "solution", "a", "temp"}:
        safe_name = f"{problem_id}{source.suffix}"
    return folder / safe_name


def git_commit(relative: Path, message: str, commit_date: datetime | None = None) -> bool:
    run("git", "add", str(relative))

    env = os.environ.copy()
    if commit_date is not None:
        iso_date = commit_date.isoformat()
        env["GIT_AUTHOR_DATE"] = iso_date
        env["GIT_COMMITTER_DATE"] = iso_date

    try:
        run("git", "commit", "-m", message, env=env)
    except subprocess.CalledProcessError:
        print("No commit was created (the file may be unchanged).")
        return False
    return True


def main() -> None:
    print("Competitive Programming - Archive Accepted Solution")
    platform = normalize_platform(input("Platform: "))
    problem_id = input("Problem id/title: ").strip()
    source_raw = input("Solution file path: ").strip().strip('"')
    source = Path(source_raw).expanduser().resolve()

    if not source.is_file():
        raise SystemExit(f"File not found: {source}")

    commit_date: datetime | None = None

    if platform == "Codeforces":
        config = load_config()
        handle = str(config.get("codeforces_handle", "")).strip()
        if handle:
            print(f"Checking Accepted submissions for {handle}...")
            accepted, accepted_at = codeforces_accepted(handle, problem_id)
            if not accepted:
                answer = input("Accepted submission was not found. Archive anyway? [y/N]: ").strip().lower()
                if answer != "y":
                    raise SystemExit("Cancelled.")
            else:
                print("Accepted submission found.")
                if accepted_at:
                    commit_date = accepted_at
                    print(f"Commit date: {accepted_at.astimezone().isoformat(timespec='seconds')}")
        else:
            print("Codeforces handle is not configured.")
            print("Run the VS Code task 'CP: Configure Codeforces handle' once.")

    destination = choose_destination(platform, problem_id, source)
    shutil.copy2(source, destination)

    relative = destination.relative_to(ROOT)
    print(f"Archived: {relative}")

    commit_label = problem_id or destination.stem
    message = f"solve({platform.lower()}): {commit_label}"

    if not git_commit(relative, message, commit_date):
        return

    print(f"Commit created: {message}")

    if "--push" in sys.argv:
        run("git", "push")
        print("Pushed to GitHub.")
    else:
        print("Commit created locally. Run git push when you want to publish it.")


if __name__ == "__main__":
    main()
