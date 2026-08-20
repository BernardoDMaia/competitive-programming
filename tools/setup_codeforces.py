from __future__ import annotations

import json
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = ROOT / ".cpconfig.json"


def validate_handle(handle: str) -> bool:
    params = urllib.parse.urlencode({"handles": handle})
    url = f"https://codeforces.com/api/user.info?{params}"
    try:
        with urllib.request.urlopen(url, timeout=10) as response:
            data = json.load(response)
    except Exception as exc:
        print(f"Could not validate handle: {exc}")
        return False
    return data.get("status") == "OK" and bool(data.get("result"))


def main() -> None:
    print("Codeforces configuration")
    handle = input("Your Codeforces handle: ").strip()
    if not handle:
        raise SystemExit("No handle provided.")

    print("Checking Codeforces...")
    if not validate_handle(handle):
        raise SystemExit("Handle not found or Codeforces API unavailable.")

    CONFIG_FILE.write_text(
        json.dumps({"codeforces_handle": handle}, indent=2) + "\n",
        encoding="utf-8",
    )

    print(f"Saved locally: {CONFIG_FILE.name}")
    print(f"Codeforces handle configured: {handle}")
    print("This file is ignored by Git and will not be published.")


if __name__ == "__main__":
    main()
