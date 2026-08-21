from __future__ import annotations

import json
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = ROOT / ".cpconfig.json"


def load_config() -> dict:
    if not CONFIG_FILE.is_file():
        return {}
    try:
        return json.loads(CONFIG_FILE.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}


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

    config = load_config()
    config["codeforces_handle"] = handle
    CONFIG_FILE.write_text(
        json.dumps(config, indent=2, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )

    print(f"Saved locally: {CONFIG_FILE.name}")
    print(f"Codeforces handle configured: {handle}")
    print("Existing local automation settings were preserved.")
    print("This file is ignored by Git and will not be published.")


if __name__ == "__main__":
    main()
