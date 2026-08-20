from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
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


def run(*args: str) -> None:
    subprocess.run(args, cwd=ROOT, check=True)


def normalize_platform(raw: str) -> str:
    key = raw.strip().lower()
    return PLATFORMS.get(key, raw.strip() or "Uncategorized")


def codeforces_accepted(handle: str, problem_id: str) -> bool:
    problem_id = problem_id.strip().upper()
    digits = "".join(ch for ch in problem_id if ch.isdigit())
    suffix = problem_id[len(digits):]
    if not digits or not suffix:
        return False

    params = urllib.parse.urlencode({"handle": handle, "from": 1, "count": 100})
    url = f"https://codeforces.com/api/user.status?{params}"

    try:
        with urllib.request.urlopen(url, timeout=8) as response:
            data = json.load(response)
    except Exception as exc:
        print(f"Warning: could not verify Codeforces submission: {exc}")
        return False

    if data.get("status") != "OK":
        return False

    contest_id = int(digits)
    index = suffix
    for submission in data.get("result", []):
        problem = submission.get("problem", {})
        if (
            submission.get("verdict") == "OK"
            and problem.get("contestId") == contest_id
            and str(problem.get("index", "")).upper() == index
        ):
            return True
    return False


def choose_destination(platform: str, problem_id: str, source: Path) -> Path:
    if platform == "USACO":
        contest = input("Contest folder (e.g. 2016-January-Gold): ").strip()
        folder = ROOT / platform / (contest or "Uncategorized")
    else:
        folder = ROOT / platform

    folder.mkdir(parents=True, exist_ok=True)
    safe_name = source.name
    if problem_id and source.stem.lower() in {"main", "solution", "a", "temp"}:
        safe_name = f"{problem_id}{source.suffix}"
    return folder / safe_name


def main() -> None:
    print("Competitive Programming — Archive Accepted Solution")
    platform = normalize_platform(input("Platform: "))
    problem_id = input("Problem id/title: ").strip()
    source_raw = input("Solution file path: ").strip().strip('"')
    source = Path(source_raw).expanduser().resolve()

    if not source.is_file():
        raise SystemExit(f"File not found: {source}")

    if platform == "Codeforces":
        handle = os.getenv("CODEFORCES_HANDLE", "").strip()
        if handle:
            print(f"Checking recent submissions for {handle}...")
            if not codeforces_accepted(handle, problem_id):
                answer = input("Accepted submission was not found. Archive anyway? [y/N]: ").strip().lower()
                if answer != "y":
                    raise SystemExit("Cancelled.")
            else:
                print("Accepted submission found.")
        else:
            print("Tip: set CODEFORCES_HANDLE to enable automatic Accepted verification.")

    destination = choose_destination(platform, problem_id, source)
    shutil.copy2(source, destination)

    relative = destination.relative_to(ROOT)
    print(f"Archived: {relative}")

    run("git", "add", str(relative))
    commit_label = problem_id or destination.stem
    message = f"solve({platform.lower()}): {commit_label}"

    try:
        run("git", "commit", "-m", message)
        print(f"Commit created: {message}")
    except subprocess.CalledProcessError:
        print("No commit was created (the file may be unchanged).")
        return

    if "--push" in sys.argv:
        run("git", "push")
        print("Pushed to GitHub.")
    else:
        print("Commit created locally. Run git push when you want to publish it.")


if __name__ == "__main__":
    main()
