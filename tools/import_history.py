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
SOURCE_EXTENSIONS = {".cpp", ".cc", ".c", ".py", ".java"}
PLATFORM_KEYS = {
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
    if not CONFIG_FILE.is_file():
        return {}
    try:
        return json.loads(CONFIG_FILE.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError):
        return {}


def fetch_codeforces_accepts(handle: str) -> dict[tuple[int, str], datetime]:
    if not handle:
        return {}

    params = urllib.parse.urlencode({"handle": handle, "from": 1, "count": 10000})
    url = f"https://codeforces.com/api/user.status?{params}"
    try:
        with urllib.request.urlopen(url, timeout=15) as response:
            data = json.load(response)
    except Exception as exc:
        print(f"Warning: could not load Codeforces history: {exc}")
        return {}

    if data.get("status") != "OK":
        return {}

    accepted: dict[tuple[int, str], datetime] = {}
    # API is newest-first; sort oldest-first so setdefault keeps first AC.
    submissions = sorted(data.get("result", []), key=lambda s: s.get("creationTimeSeconds", 0))
    for submission in submissions:
        if submission.get("verdict") != "OK":
            continue
        problem = submission.get("problem", {})
        contest_id = problem.get("contestId")
        index = str(problem.get("index", "")).upper()
        timestamp = submission.get("creationTimeSeconds")
        if contest_id is None or not index or not timestamp:
            continue
        accepted.setdefault(
            (int(contest_id), index),
            datetime.fromtimestamp(timestamp, tz=timezone.utc),
        )
    return accepted


def infer_platform(path: Path) -> str | None:
    parts = [part.lower() for part in path.parts]
    for key, platform in PLATFORM_KEYS.items():
        if key in parts:
            return platform
    joined = " ".join(parts)
    for key, platform in PLATFORM_KEYS.items():
        if key in joined:
            return platform
    return None


def infer_codeforces_id(path: Path, source_root: Path) -> tuple[int, str] | None:
    stem = path.stem
    direct = re.fullmatch(r"(\d+)([A-Za-z][A-Za-z0-9]*)", stem)
    if direct:
        return int(direct.group(1)), direct.group(2).upper()

    index_match = re.fullmatch(r"([A-Za-z][A-Za-z0-9]*)", stem)
    if not index_match:
        return None

    index = index_match.group(1).upper()
    try:
        relatives = path.relative_to(source_root).parts[:-1]
    except ValueError:
        relatives = path.parts[:-1]

    for part in reversed(relatives):
        contest_match = re.search(r"(?<!\d)(\d{3,6})(?!\d)", part)
        if contest_match:
            return int(contest_match.group(1)), index
    return None


def destination_for(path: Path, source_root: Path, platform: str, cf_id: tuple[int, str] | None) -> Path:
    suffix = path.suffix.lower()
    if platform == "Codeforces" and cf_id:
        contest_id, index = cf_id
        return ROOT / "Codeforces" / str(contest_id) / f"{contest_id}{index}{suffix}"

    relative = path.relative_to(source_root)
    parts = list(relative.parts)
    if parts and parts[0].lower() in PLATFORM_KEYS:
        parts = parts[1:]
    if not parts:
        parts = [path.name]
    return ROOT / platform / Path(*parts)


def git_commit(relative: Path, message: str, when: datetime) -> bool:
    run("git", "add", str(relative))
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
    print("Competitive Programming - Historical Import")
    print("This tool commits old solutions using real Codeforces AC timestamps when available.")
    print("For other platforms, the local file modification time is used as a fallback.\n")

    raw = sys.argv[1] if len(sys.argv) > 1 and not sys.argv[1].startswith("--") else input("Folder with old solutions: ")
    source_root = Path(raw.strip().strip('"')).expanduser().resolve()
    if not source_root.is_dir():
        raise SystemExit(f"Folder not found: {source_root}")

    config = load_config()
    handle = str(config.get("codeforces_handle", "")).strip()
    cf_accepts: dict[tuple[int, str], datetime] = {}
    if handle:
        print(f"Loading Accepted history for Codeforces handle {handle}...")
        cf_accepts = fetch_codeforces_accepts(handle)
        print(f"Loaded {len(cf_accepts)} accepted Codeforces problems.\n")
    else:
        print("Codeforces handle is not configured; Codeforces dates will fall back to file timestamps.\n")

    files = sorted(
        p for p in source_root.rglob("*")
        if p.is_file() and p.suffix.lower() in SOURCE_EXTENSIONS and ROOT not in p.parents
    )
    if not files:
        raise SystemExit("No source files found.")

    entries = []
    for path in files:
        platform = infer_platform(path)
        if platform is None:
            platform = "Uncategorized"

        cf_id = infer_codeforces_id(path, source_root) if platform == "Codeforces" else None
        date_source = "file modified time"
        when = datetime.fromtimestamp(path.stat().st_mtime, tz=timezone.utc)

        if platform == "Codeforces" and cf_id and cf_id in cf_accepts:
            when = cf_accepts[cf_id]
            date_source = "Codeforces Accepted"

        destination = destination_for(path, source_root, platform, cf_id)
        entries.append((when, path, destination, platform, cf_id, date_source))

    entries.sort(key=lambda item: item[0])

    print(f"Found {len(entries)} source files. Preview:\n")
    for when, path, destination, platform, cf_id, date_source in entries:
        label = f"{cf_id[0]}{cf_id[1]}" if cf_id else path.stem
        print(f"[{when.astimezone().strftime('%Y-%m-%d %H:%M')}] {platform:13} {label:15} <- {date_source}")
        print(f"    {path}")
        print(f" -> {destination.relative_to(ROOT)}")

    print("\nImportant: only dates marked 'Codeforces Accepted' come from the platform itself.")
    print("Other dates are based on your local file metadata and should be reviewed if accuracy matters.")

    if "--preview" in sys.argv:
        print("\nPreview only; no files or commits were created.")
        return

    confirm = input("\nCreate these historical commits? Type IMPORT to confirm: ").strip()
    if confirm != "IMPORT":
        raise SystemExit("Cancelled.")

    created = 0
    skipped = 0
    for when, source, destination, platform, cf_id, date_source in entries:
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)
        relative = destination.relative_to(ROOT)

        if cf_id:
            label = f"{cf_id[0]}{cf_id[1]}"
        else:
            label = source.stem
        message = f"solve({platform.lower()}): {label}"

        if git_commit(relative, message, when):
            created += 1
            print(f"Committed {relative} [{date_source}]")
        else:
            skipped += 1
            print(f"Skipped {relative} (unchanged or already tracked)")

    print(f"\nDone: {created} commits created, {skipped} skipped.")
    if "--push" in sys.argv and created:
        run("git", "push")
        print("Historical commits pushed to GitHub.")
    elif created:
        print("Review with: git log --date=iso --pretty=format:'%h %ad %s'")
        print("Then publish with: git push")


if __name__ == "__main__":
    main()
