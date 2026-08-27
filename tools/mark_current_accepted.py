from __future__ import annotations

import shutil
import sys
from datetime import datetime, timezone
from pathlib import Path

from finish_current_problem import (
    ROOT,
    SOURCE_EXTENSIONS,
    choose_nonconflicting_destination,
    detect_destination,
    find_cph_metadata,
    git_commit_move,
    move_cph_metadata,
    normalize_path,
)


def main() -> None:
    if len(sys.argv) < 2:
        raise SystemExit(
            "Usage: python tools/mark_current_accepted.py <current-file>"
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

    if platform == "Codeforces":
        raise SystemExit(
            "This command is for non-Codeforces problems. "
            "Codeforces Accepted solutions are handled by the automatic workflow."
        )

    # If CPH already created the file exactly where our organizer wants it,
    # that does NOT mean it has already been archived in Git. In this case we
    # must still stage and commit the file when the user confirms Accepted.
    source_is_destination = normalize_path(source) == normalize_path(destination)
    if source_is_destination:
        already_same = False
        destination = source
    else:
        destination, already_same = choose_nonconflicting_destination(destination, source)

    accepted_at = datetime.now(timezone.utc)

    print("\nManual Accepted confirmation")
    print(f"  Platform:    {platform}")
    print(f"  Problem:     {problem_label}")
    print(f"  Source:      {source}")
    print(f"  Destination: {destination}")
    print(f"  Commit date: {accepted_at.astimezone().isoformat(timespec='seconds')}")
    print("  Date source: time you triggered the Accepted command")

    if already_same:
        print("\nThe same solution is already archived at the destination.")
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

    platform_label = platform.lower().replace(" ", "-")
    message = f"solve({platform_label}): {problem_label}"

    if not git_commit_move(original_source, destination, message, accepted_at):
        print(
            "No commit was created. The solution is already committed unchanged, "
            "or there are no Git changes for this file."
        )
        return

    print(f"\nAccepted solution committed locally: {message}")
    print(f"Archived at: {destination.relative_to(ROOT)}")
    print("No push was performed. This commit will be included in the next weekly push.")


if __name__ == "__main__":
    main()
