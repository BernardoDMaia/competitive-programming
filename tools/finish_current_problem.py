from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path
from urllib.parse import parse_qs, urlparse

from archive_solution import codeforces_accepted, load_config

ROOT = Path(__file__).resolve().parents[1]
SOURCE_EXTENSIONS = {".cpp", ".cc", ".c", ".py", ".java", ".rs", ".go"}


def run(*args: str, env: dict[str, str] | None = None) -> subprocess.CompletedProcess:
    return subprocess.run(args, cwd=ROOT, check=True, env=env)


def normalize_path(value: str | Path) -> str:
    return os.path.normcase(os.path.abspath(str(value)))


def slug(text: str) -> str:
    text = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", text)
    words = re.findall(r"[A-Za-z0-9]+", text)
    return "-".join(words) or "problem"


def compact_slug(text: str) -> str:
    return slug(text).lower()


def find_cph_metadata(source: Path) -> tuple[dict, Path] | None:
    candidates: list[Path] = []
    default_dir = source.parent / ".cph"
    if default_dir.is_dir():
        candidates.extend(default_dir.glob("*.prob"))

    # Also scan the repository in case CPH metadata is configured into another
    # folder inside the workspace.
    for path in ROOT.rglob("*.prob"):
        if path not in candidates:
            candidates.append(path)

    wanted = normalize_path(source)
    fallback: tuple[dict, Path] | None = None

    for path in candidates:
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            continue

        src_path = str(data.get("srcPath", "")).strip()
        if src_path and normalize_path(src_path) == wanted:
            return data, path

        if src_path and Path(src_path).name.lower() == source.name.lower():
            fallback = (data, path)

    return fallback


def codeforces_info(url: str) -> tuple[int, str] | None:
    patterns = [
        r"/contest/(\d+)/problem/([A-Za-z0-9]+)",
        r"/problemset/problem/(\d+)/([A-Za-z0-9]+)",
    ]
    for pattern in patterns:
        match = re.search(pattern, url)
        if match:
            return int(match.group(1)), match.group(2).upper()
    return None


def usaco_contest_folder(group: str) -> str:
    month_match = re.search(
        r"\b(January|February|March|April|May|June|July|August|September|October|November|December)\b",
        group,
        re.I,
    )
    year_match = re.search(r"\b(20\d{2})\b", group)
    division_match = re.search(r"\b(Bronze|Silver|Gold|Platinum)\b", group, re.I)

    if year_match and month_match and division_match:
        return (
            f"{year_match.group(1)}-"
            f"{month_match.group(1).title()}-"
            f"{division_match.group(1).title()}"
        )
    return "Uncategorized"


def detect_destination(metadata: dict, source: Path) -> tuple[str, str, Path]:
    url = str(metadata.get("url", "")).strip()
    name = str(metadata.get("name", source.stem)).strip() or source.stem
    group = str(metadata.get("group", "")).strip()
    parsed = urlparse(url)
    host = parsed.netloc.lower()
    ext = source.suffix.lower()

    cf = codeforces_info(url)
    if cf:
        contest_id, index = cf
        problem_id = f"{contest_id}{index}"
        return "Codeforces", problem_id, ROOT / "Codeforces" / str(contest_id) / f"{problem_id}{ext}"

    if "atcoder.jp" in host:
        match = re.search(r"/contests/([^/]+)/tasks/[^/]+_([A-Za-z0-9]+)", parsed.path)
        if match:
            contest = match.group(1).upper()
            index = match.group(2).upper()
            return "AtCoder", f"{contest}-{index}", ROOT / "AtCoder" / contest / f"{index}{ext}"
        return "AtCoder", name, ROOT / "AtCoder" / "Uncategorized" / f"{slug(name)}{ext}"

    if "cses.fi" in host:
        match = re.search(r"/problemset/task/(\d+)", parsed.path)
        if match:
            task_id = match.group(1)
            return "CSES", task_id, ROOT / "CSES" / f"{task_id}-{slug(name)}{ext}"
        return "CSES", name, ROOT / "CSES" / f"{slug(name)}{ext}"

    if "usaco.org" in host:
        query = parse_qs(parsed.query)
        cpid = query.get("cpid", [""])[0]
        label = cpid or name
        folder = usaco_contest_folder(group)
        return "USACO", label, ROOT / "USACO" / folder / f"{compact_slug(name)}{ext}"

    if "beecrowd" in host or "urionlinejudge" in host:
        match = re.search(r"/(?:problems/view|problems)/(\d+)", parsed.path)
        problem_id = match.group(1) if match else slug(name)
        return "Beecrowd", problem_id, ROOT / "Beecrowd" / f"{problem_id}{ext}"

    if "spoj.com" in host:
        match = re.search(r"/problems/([^/]+)", parsed.path, re.I)
        problem_id = match.group(1).upper() if match else slug(name)
        return "SPOJ", problem_id, ROOT / "SPOJ" / f"{problem_id}{ext}"

    if "kattis.com" in host:
        match = re.search(r"/problems/([^/]+)", parsed.path)
        problem_id = match.group(1) if match else compact_slug(name)
        return "Kattis", problem_id, ROOT / "Kattis" / f"{problem_id}{ext}"

    if "olimpiada.ic.unicamp.br" in host or re.search(r"\bOBI\b", group, re.I):
        return "OBI", name, ROOT / "OBI" / f"{slug(name)}{ext}"

    if re.search(r"\bICPC\b", group, re.I):
        group_folder = slug(group)
        return "ICPC", name, ROOT / "ICPC" / group_folder / f"{slug(name)}{ext}"

    host_folder = slug(host or "unknown-source")
    return "Other", name, ROOT / "Other" / host_folder / f"{slug(name)}{ext}"


def choose_nonconflicting_destination(destination: Path, source: Path) -> tuple[Path, bool]:
    if not destination.exists():
        return destination, False

    try:
        if destination.read_bytes() == source.read_bytes():
            return destination, True
    except OSError:
        pass

    for i in range(2, 100):
        candidate = destination.with_name(f"{destination.stem}-alt{i}{destination.suffix}")
        if not candidate.exists():
            return candidate, False

    raise SystemExit(f"Could not find a free destination near {destination}")


def relocated_prob_path(old_prob: Path, destination: Path) -> Path:
    # Default CPH behavior stores .prob under a sibling .cph directory.
    # If the user configured a custom metadata directory, preserve it.
    if old_prob.parent.name.lower() == ".cph":
        metadata_dir = destination.parent / ".cph"
    else:
        metadata_dir = old_prob.parent

    metadata_dir.mkdir(parents=True, exist_ok=True)
    digest = hashlib.md5(str(destination).encode("utf-8")).hexdigest()
    return metadata_dir / f".{destination.name}_{digest}.prob"


def move_cph_metadata(metadata: dict, old_prob: Path, destination: Path) -> None:
    metadata = dict(metadata)
    metadata["srcPath"] = str(destination)

    new_prob = relocated_prob_path(old_prob, destination)
    new_prob.write_text(json.dumps(metadata, ensure_ascii=False), encoding="utf-8")

    if normalize_path(new_prob) != normalize_path(old_prob):
        try:
            old_prob.unlink()
        except OSError:
            pass

    try:
        if (
            old_prob.parent.name.lower() == ".cph"
            and old_prob.parent.exists()
            and not any(old_prob.parent.iterdir())
        ):
            old_prob.parent.rmdir()
    except OSError:
        pass


def relative_if_inside(path: Path) -> Path | None:
    try:
        return path.resolve().relative_to(ROOT.resolve())
    except ValueError:
        return None


def git_path_is_tracked(relative: Path) -> bool:
    result = subprocess.run(
        ["git", "ls-files", "--error-unmatch", "--", str(relative)],
        cwd=ROOT,
        check=False,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return result.returncode == 0


def git_commit_move(source: Path, destination: Path, message: str, when: datetime) -> bool:
    paths: list[str] = []
    source_rel = relative_if_inside(source)
    dest_rel = relative_if_inside(destination)

    # After shutil.move(), a temporary CPH source often no longer exists and was
    # never tracked by Git. Passing that vanished untracked path to `git add`
    # makes Git fail with "pathspec did not match any files". Include the old
    # path only when it still exists or the index already knows about it.
    if source_rel is not None and (source.exists() or git_path_is_tracked(source_rel)):
        paths.append(str(source_rel))
    if dest_rel is not None and str(dest_rel) not in paths:
        paths.append(str(dest_rel))

    if not paths:
        raise SystemExit("Neither source nor destination is inside the repository.")

    run("git", "add", "-A", "--", *paths)

    env = os.environ.copy()
    iso_date = when.isoformat()
    env["GIT_AUTHOR_DATE"] = iso_date
    env["GIT_COMMITTER_DATE"] = iso_date

    try:
        run("git", "commit", "-m", message, env=env)
        return True
    except subprocess.CalledProcessError:
        return False


def main() -> None:
    if len(sys.argv) < 2 or sys.argv[1].startswith("--"):
        raise SystemExit(
            "Usage: python tools/finish_current_problem.py <current-file> [--push]"
        )

    source = Path(sys.argv[1].strip().strip('"')).expanduser().resolve()
    if not source.is_file():
        raise SystemExit(f"Current file was not found: {source}")
    if source.suffix.lower() not in SOURCE_EXTENSIONS:
        raise SystemExit(f"Unsupported source extension: {source.suffix}")

    found = find_cph_metadata(source)
    if found is None:
        raise SystemExit(
            "CPH metadata was not found for this file. "
            "Import the problem with Competitive Companion first."
        )

    metadata, prob_path = found
    platform, problem_label, destination = detect_destination(metadata, source)
    destination, already_same = choose_nonconflicting_destination(destination, source)

    modified_at = datetime.fromtimestamp(source.stat().st_mtime, tz=timezone.utc)
    commit_date = modified_at
    date_source = "file modification time"

    if platform == "Codeforces":
        config = load_config()
        handle = str(config.get("codeforces_handle", "")).strip()
        if not handle:
            raise SystemExit(
                "Codeforces handle is not configured. "
                "Run 'CP: Configure Codeforces handle' first."
            )

        accepted, accepted_at = codeforces_accepted(handle, problem_label)
        if not accepted:
            raise SystemExit(
                f"No Accepted submission found for {problem_label} on Codeforces. "
                "The file was left untouched."
            )
        if accepted_at is not None:
            commit_date = accepted_at
            date_source = "Codeforces first Accepted"

    print("\nDetected problem")
    print(f"  Platform:    {platform}")
    print(f"  Problem:     {problem_label}")
    print(f"  Source:      {source}")
    print(f"  Destination: {destination}")
    print(f"  Commit date: {commit_date.astimezone().isoformat(timespec='seconds')}")
    print(f"  Date source: {date_source}")

    if already_same:
        print("\nThe same solution is already archived at the destination.")
        if normalize_path(source) != normalize_path(destination):
            source.unlink()
            move_cph_metadata(metadata, prob_path, destination)
        return

    answer = input("\nFinish this problem? [Y/n]: ").strip().lower()
    if answer not in {"", "y", "yes"}:
        raise SystemExit("Cancelled.")

    destination.parent.mkdir(parents=True, exist_ok=True)
    original_source = source

    if normalize_path(source) != normalize_path(destination):
        shutil.move(str(source), str(destination))
    else:
        destination = source

    move_cph_metadata(metadata, prob_path, destination)

    platform_label = platform.lower().replace(" ", "-")
    message = f"solve({platform_label}): {problem_label}"

    if not git_commit_move(original_source, destination, message, commit_date):
        print("No commit was created (the solution may already be tracked unchanged).")
        return

    print(f"\nCommit created: {message}")
    print(f"Archived at: {destination.relative_to(ROOT)}")

    if "--push" in sys.argv:
        run("git", "push", "origin", "main")
        print("Pushed to GitHub.")
    else:
        print("Commit is local. Run git push when you want to publish it.")


if __name__ == "__main__":
    main()
