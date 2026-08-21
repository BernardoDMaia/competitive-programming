from __future__ import annotations

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def run(*args: str, capture: bool = False) -> subprocess.CompletedProcess:
    return subprocess.run(
        args,
        cwd=ROOT,
        check=True,
        text=True,
        capture_output=capture,
    )


def main() -> None:
    branch = run("git", "branch", "--show-current", capture=True).stdout.strip()
    if branch != "main":
        raise SystemExit(f"Weekly push skipped: current branch is '{branch}', not 'main'.")

    try:
        run("git", "fetch", "origin", "main")
    except subprocess.CalledProcessError as exc:
        raise SystemExit(f"Weekly push skipped: git fetch failed ({exc}).")

    behind = int(
        run("git", "rev-list", "--count", "HEAD..origin/main", capture=True).stdout.strip() or "0"
    )
    if behind:
        raise SystemExit(
            f"Weekly push skipped: local main is behind origin/main by {behind} commit(s). "
            "Pull/reconcile manually before publishing."
        )

    pending = int(
        run("git", "rev-list", "--count", "origin/main..HEAD", capture=True).stdout.strip() or "0"
    )
    if pending == 0:
        print("Weekly push: no pending commits.")
        return

    print(f"Weekly push: publishing {pending} pending commit(s)...")
    run("git", "push", "origin", "main")
    print("Weekly push completed successfully.")


if __name__ == "__main__":
    main()
