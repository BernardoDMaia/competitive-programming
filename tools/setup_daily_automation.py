from __future__ import annotations

import json
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = ROOT / ".cpconfig.json"
STATE_FILE = ROOT / ".cp-watcher-state.json"

DAYS = {
    "mon": 0, "monday": 0, "segunda": 0,
    "tue": 1, "tuesday": 1, "terca": 1, "terça": 1,
    "wed": 2, "wednesday": 2, "quarta": 2,
    "thu": 3, "thursday": 3, "quinta": 3,
    "fri": 4, "friday": 4, "sexta": 4,
    "sat": 5, "saturday": 5, "sabado": 5, "sábado": 5,
    "sun": 6, "sunday": 6, "domingo": 6,
}


def load_json(path: Path) -> dict:
    if not path.is_file():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}


def main() -> None:
    print("Competitive programming automation configuration")
    day_raw = input("Weekly push day [Sunday]: ").strip().lower() or "sunday"
    if day_raw not in DAYS:
        raise SystemExit("Invalid day. Example: Sunday, domingo, Saturday, sábado.")

    time_raw = input("Weekly push time in HH:MM [20:00]: ").strip() or "20:00"
    try:
        hour, minute = [int(x) for x in time_raw.split(":", 1)]
        if not (0 <= hour <= 23 and 0 <= minute <= 59):
            raise ValueError
    except ValueError:
        raise SystemExit("Invalid time. Use HH:MM, for example 20:00.")

    config = load_json(CONFIG_FILE)
    config["weekly_push"] = {
        "enabled": True,
        "weekday": DAYS[day_raw],
        "day_name": day_raw,
        "hour": hour,
        "minute": minute,
    }
    CONFIG_FILE.write_text(
        json.dumps(config, indent=2, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )

    # Treat configuration time as the baseline so enabling the feature does not
    # immediately publish commits because of a schedule occurrence from last week.
    state = load_json(STATE_FILE)
    state["last_weekly_push"] = datetime.now().astimezone().isoformat()
    STATE_FILE.write_text(json.dumps(state, indent=2) + "\n", encoding="utf-8")

    print(f"Weekly push configured for {day_raw} at {hour:02d}:{minute:02d}.")
    print("The first automatic push will happen at the next scheduled occurrence.")
    print("The Codeforces watcher performs the push when this workspace is open.")
    print("If VS Code was closed at that time, it pushes on the next workspace opening.")


if __name__ == "__main__":
    main()
