from __future__ import annotations

import hashlib
import html
import json
import os
import re
import shutil
import subprocess
import sys
import urllib.parse
import urllib.request
from dataclasses import dataclass
from datetime import datetime, timedelta, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = ROOT / ".cpconfig.json"
PLAN_FILE = ROOT / ".cp-import-plan.json"
SOURCE_EXTENSIONS = {".cpp", ".cc", ".c", ".py", ".java"}

PLATFORM_DIR_HINTS = {
    "codeforces": "Codeforces",
    "cf": "Codeforces",
    "cses": "CSES",
    "atcoder": "AtCoder",
    "obi": "OBI",
    "beecrowd": "Beecrowd",
    "uri": "Beecrowd",
    "usaco": "USACO",
}

ICPC_PATTERNS = [
    (re.compile(r"\bnwerc[\s._-]*(20)?(\d{2})\b", re.I), "NWERC"),
    (re.compile(r"\bswerc[\s._-]*(20)?(\d{2})\b", re.I), "SWERC"),
    (re.compile(r"\bnaq[\s._-]*(20)?(\d{2})\b", re.I), "NAQ"),
    (re.compile(r"\bsub(?:regional)?[\s._-]*(20)?(\d{2})\b", re.I), "Brazil-Subregional"),
]


@dataclass
class CodeforcesProblem:
    contest_id: int
    index: str
    name: str
    first_ac: datetime


@dataclass
class Candidate:
    source: Path
    source_root: Path
    platform: str | None
    problem_key: str
    destination: Path | None
    when: datetime
    date_source: str
    confidence: str
    reason: str
    content_hash: str
    status: str = "READY"


def run(*args: str, env: dict[str, str] | None = None) -> subprocess.CompletedProcess:
    return subprocess.run(args, cwd=ROOT, check=True, env=env)


def load_config() -> dict:
    if not CONFIG_FILE.is_file():
        return {}
    try:
        return json.loads(CONFIG_FILE.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError):
        return {}


def save_config(config: dict) -> None:
    CONFIG_FILE.write_text(json.dumps(config, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def configure_sources() -> None:
    config = load_config()
    current = [str(Path(p)) for p in config.get("history_sources", []) if str(p).strip()]

    print("Competitive Programming - Configure Historical Folders")
    if current:
        print("\nCurrent folders:")
        for i, folder in enumerate(current, 1):
            print(f"  {i}. {folder}")

    print("\nEnter one folder per line. Press Enter on an empty line when finished.")
    print("The folder name itself is NOT used as a platform hint; only its contents are scanned.")
    new_sources: list[str] = []

    while True:
        raw = input("Folder: ").strip().strip('"')
        if not raw:
            break
        path = Path(raw).expanduser().resolve()
        if not path.is_dir():
            print(f"  Not found: {path}")
            continue
        if path == ROOT or ROOT in path.parents:
            print("  Skip: do not use the repository itself as a historical source.")
            continue
        value = str(path)
        if value not in new_sources:
            new_sources.append(value)
            print(f"  Added: {path}")

    if not new_sources:
        if current:
            print("\nNo changes made.")
            return
        raise SystemExit("No valid folders were configured.")

    config["history_sources"] = new_sources
    save_config(config)
    print(f"\nSaved {len(new_sources)} historical source folder(s) to local .cpconfig.json.")


def normalize_title(text: str) -> str:
    text = Path(text).stem
    text = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", text)
    text = re.sub(r"^[A-Za-z]\s*[_\-.]\s*", "", text)
    text = text.replace("_", " ").replace("-", " ").replace(".", " ")
    text = html.unescape(text).lower()
    return " ".join(re.findall(r"[a-z0-9]+", text))


def slug(text: str) -> str:
    words = re.findall(r"[A-Za-z0-9]+", re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", text))
    return "-".join(words) or "problem"


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as fh:
        for chunk in iter(lambda: fh.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def fetch_codeforces_history(handle: str) -> tuple[dict[tuple[int, str], CodeforcesProblem], dict[str, list[CodeforcesProblem]]]:
    if not handle:
        return {}, {}

    params = urllib.parse.urlencode({"handle": handle, "from": 1, "count": 10000})
    url = f"https://codeforces.com/api/user.status?{params}"
    try:
        with urllib.request.urlopen(url, timeout=20) as response:
            data = json.load(response)
    except Exception as exc:
        print(f"Warning: could not load Codeforces history: {exc}")
        return {}, {}

    if data.get("status") != "OK":
        print("Warning: Codeforces returned a non-OK response.")
        return {}, {}

    by_id: dict[tuple[int, str], CodeforcesProblem] = {}
    submissions = sorted(data.get("result", []), key=lambda s: s.get("creationTimeSeconds", 0))
    for submission in submissions:
        if submission.get("verdict") != "OK":
            continue
        problem = submission.get("problem", {})
        contest_id = problem.get("contestId")
        index = str(problem.get("index", "")).upper()
        name = str(problem.get("name", "")).strip()
        timestamp = submission.get("creationTimeSeconds")
        if contest_id is None or not index or not name or not timestamp:
            continue
        key = (int(contest_id), index)
        if key not in by_id:
            by_id[key] = CodeforcesProblem(
                int(contest_id), index, name,
                datetime.fromtimestamp(timestamp, tz=timezone.utc),
            )

    by_title: dict[str, list[CodeforcesProblem]] = {}
    for problem in by_id.values():
        by_title.setdefault(normalize_title(problem.name), []).append(problem)
    return by_id, by_title


def fetch_cses_catalog() -> dict[str, tuple[str, str]]:
    try:
        request = urllib.request.Request("https://cses.fi/problemset/", headers={"User-Agent": "Mozilla/5.0"})
        with urllib.request.urlopen(request, timeout=15) as response:
            text = response.read().decode("utf-8", errors="replace")
    except Exception as exc:
        print(f"Warning: could not load CSES problem catalog: {exc}")
        return {}

    matches = re.findall(r'href=["\']/problemset/task/(\d+)["\'][^>]*>(.*?)</a>', text, flags=re.I | re.S)
    catalog: dict[str, tuple[str, str]] = {}
    for task_id, raw_title in matches:
        title = re.sub(r"<[^>]+>", "", raw_title)
        title = html.unescape(title).strip()
        if title:
            catalog[normalize_title(title)] = (task_id, title)
    return catalog


def rel_parts(path: Path, source_root: Path) -> list[str]:
    return list(path.relative_to(source_root).parts)


def explicit_platform(parts: list[str]) -> tuple[str | None, int | None, str]:
    for i, part in enumerate(parts[:-1]):
        lower = part.lower()
        compact = re.sub(r"[^a-z0-9]+", "", lower)
        tokens = set(re.findall(r"[a-z0-9]+", lower))
        if "usacoguide" in compact:
            continue
        for hint, platform in PLATFORM_DIR_HINTS.items():
            if lower == hint or hint in tokens:
                return platform, i, f"folder '{part}'"
    return None, None, ""


def infer_icpc(parts: list[str]) -> tuple[str | None, Path | None, str]:
    for i, part in enumerate(parts[:-1]):
        compact = re.sub(r"[^a-z0-9]+", "", part.lower())
        if "maratonamineira" in compact:
            tail = Path(*parts[i + 1 :])
            return "ICPC", Path("ICPC") / "Maratona-Mineira" / tail, f"contest folder '{part}'"
        if "meiamaratona" in compact:
            tail = Path(*parts[i + 1 :])
            return "ICPC", Path("ICPC") / "Meia-Maratona" / tail, f"contest folder '{part}'"
        for pattern, event in ICPC_PATTERNS:
            match = pattern.search(part)
            if match:
                year = f"20{match.group(2)}"
                tail = Path(*parts[i + 1 :])
                return "ICPC", Path("ICPC") / event / year / tail, f"contest folder '{part}'"
    return None, None, ""


def direct_cf_id(path: Path, parts: list[str]) -> tuple[int, str] | None:
    stem = path.stem
    match = re.fullmatch(r"(\d{3,6})([A-Za-z][A-Za-z0-9]*)", stem)
    if match:
        return int(match.group(1)), match.group(2).upper()
    if re.fullmatch(r"[A-Za-z][A-Za-z0-9]*", stem):
        for part in reversed(parts[:-1]):
            contest = re.fullmatch(r"\D*(\d{3,6})\D*", part)
            if contest:
                return int(contest.group(1)), stem.upper()
    return None


def cf_title_match(path: Path, by_title: dict[str, list[CodeforcesProblem]]) -> CodeforcesProblem | None:
    matches = by_title.get(normalize_title(path.stem), [])
    return matches[0] if len(matches) == 1 else None


def strong_cf_hint(parts: list[str]) -> bool:
    joined = " ".join(p.lower() for p in parts[:-1])
    return bool(re.search(r"\b(div[1-4]|educational|codeforces|cfround|contest\.?div)\b", joined))


def cf_time_index_match(path: Path, by_id: dict[tuple[int, str], CodeforcesProblem], hinted: bool) -> CodeforcesProblem | None:
    if not hinted or not re.fullmatch(r"[A-Za-z][A-Za-z0-9]*", path.stem):
        return None
    index = path.stem.upper()
    modified = datetime.fromtimestamp(path.stat().st_mtime, tz=timezone.utc)
    matches = [
        p for p in by_id.values()
        if p.index == index and abs(p.first_ac - modified) <= timedelta(hours=72)
    ]
    return matches[0] if len(matches) == 1 else None


def usaco_guide_hint(parts: list[str]) -> tuple[bool, int | None]:
    for i, part in enumerate(parts[:-1]):
        if "usacoguide" in re.sub(r"[^a-z0-9]+", "", part.lower()):
            return True, i
    return False, None


def explicit_destination(platform: str, parts: list[str], marker: int, path: Path) -> Path:
    tail = parts[marker + 1 :] or [path.name]
    if platform == "AtCoder" and len(tail) >= 2 and re.fullmatch(r"\d{2,5}", tail[0]):
        tail[-1] = f"{Path(tail[-1]).stem.upper()}{path.suffix.lower()}"
    return Path(platform) / Path(*tail)


def classify(path: Path, source_root: Path, cf_by_id, cf_by_title, cses_catalog) -> Candidate:
    parts = rel_parts(path, source_root)
    when = datetime.fromtimestamp(path.stat().st_mtime, tz=timezone.utc)
    date_source = "file modified time"
    content_hash = sha256_file(path)

    platform, marker, reason = explicit_platform(parts)
    if platform:
        if platform == "Codeforces":
            cf_id = direct_cf_id(path, parts)
            problem = cf_by_id.get(cf_id) if cf_id else None
            problem = problem or cf_title_match(path, cf_by_title)
            problem = problem or cf_time_index_match(path, cf_by_id, strong_cf_hint(parts))
            if problem:
                dest = ROOT / "Codeforces" / str(problem.contest_id) / f"{problem.contest_id}{problem.index}{path.suffix.lower()}"
                return Candidate(path, source_root, "Codeforces", f"{problem.contest_id}{problem.index}", dest,
                                 problem.first_ac, "Codeforces first Accepted", "HIGH",
                                 f"{reason}; matched Codeforces history", content_hash)
        dest = ROOT / explicit_destination(platform, parts, marker or 0, path)
        return Candidate(path, source_root, platform, path.stem, dest, when, date_source, "HIGH", reason, content_hash)

    icpc_platform, icpc_dest, icpc_reason = infer_icpc(parts)
    if icpc_platform and icpc_dest:
        return Candidate(path, source_root, icpc_platform, path.stem, ROOT / icpc_dest, when, date_source,
                         "HIGH", icpc_reason, content_hash)

    cf_id = direct_cf_id(path, parts)
    if cf_id and cf_id in cf_by_id:
        problem = cf_by_id[cf_id]
        dest = ROOT / "Codeforces" / str(problem.contest_id) / f"{problem.contest_id}{problem.index}{path.suffix.lower()}"
        return Candidate(path, source_root, "Codeforces", f"{problem.contest_id}{problem.index}", dest,
                         problem.first_ac, "Codeforces first Accepted", "HIGH",
                         "problem id matched Codeforces history", content_hash)

    problem = cf_title_match(path, cf_by_title)
    if problem:
        dest = ROOT / "Codeforces" / str(problem.contest_id) / f"{problem.contest_id}{problem.index}{path.suffix.lower()}"
        return Candidate(path, source_root, "Codeforces", f"{problem.contest_id}{problem.index}", dest,
                         problem.first_ac, "Codeforces first Accepted", "HIGH",
                         f"title matched '{problem.name}' in Codeforces history", content_hash)

    normalized = normalize_title(path.stem)
    if normalized in cses_catalog:
        task_id, title = cses_catalog[normalized]
        dest = ROOT / "CSES" / f"{task_id}-{slug(title)}{path.suffix.lower()}"
        return Candidate(path, source_root, "CSES", task_id, dest, when, date_source, "HIGH",
                         f"title matched CSES problem '{title}'", content_hash)

    problem = cf_time_index_match(path, cf_by_id, strong_cf_hint(parts))
    if problem:
        dest = ROOT / "Codeforces" / str(problem.contest_id) / f"{problem.contest_id}{problem.index}{path.suffix.lower()}"
        return Candidate(path, source_root, "Codeforces", f"{problem.contest_id}{problem.index}", dest,
                         problem.first_ac, "Codeforces first Accepted", "MEDIUM",
                         "unique Codeforces index + nearby local timestamp", content_hash)

    guide, guide_index = usaco_guide_hint(parts)
    if guide and guide_index is not None:
        tail = parts[guide_index + 1 :] or [path.name]
        dest = ROOT / "Study" / "USACO-Guide" / Path(*tail)
        return Candidate(path, source_root, "USACO Guide", path.stem, dest, when, date_source, "MEDIUM",
                         f"study folder '{parts[guide_index]}' (platform unresolved)", content_hash)

    return Candidate(path, source_root, None, path.stem, None, when, date_source, "UNRESOLVED",
                     "no reliable platform/problem match", content_hash, status="UNRESOLVED")


def source_roots(config: dict) -> list[Path]:
    roots: list[Path] = []
    for value in config.get("history_sources", []):
        path = Path(str(value)).expanduser().resolve()
        if path.is_dir() and path != ROOT and ROOT not in path.parents and path not in roots:
            roots.append(path)
    return roots


def collect_files(roots: list[Path]) -> list[tuple[Path, Path]]:
    result: list[tuple[Path, Path]] = []
    seen: set[Path] = set()
    for root in roots:
        for path in root.rglob("*"):
            if path.is_file() and path.suffix.lower() in SOURCE_EXTENSIONS:
                resolved = path.resolve()
                if resolved not in seen:
                    seen.add(resolved)
                    result.append((resolved, root))
    return result


def existing_hashes() -> set[str]:
    hashes: set[str] = set()
    excluded = {".git", ".vscode", "tools", "__pycache__"}
    for path in ROOT.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in SOURCE_EXTENSIONS:
            continue
        rel = path.relative_to(ROOT)
        if any(part in excluded for part in rel.parts):
            continue
        hashes.add(sha256_file(path))
    return hashes


def apply_duplicate_rules(entries: list[Candidate]) -> None:
    tracked = existing_hashes()
    seen_hashes: dict[str, Candidate] = {}
    destination_counts: dict[str, int] = {}

    for entry in entries:
        if entry.status == "UNRESOLVED":
            continue
        if entry.content_hash in tracked:
            entry.status = "ALREADY-TRACKED"
            continue
        if entry.content_hash in seen_hashes:
            entry.status = "DUPLICATE"
            entry.reason += f"; same code as {seen_hashes[entry.content_hash].source}"
            continue
        seen_hashes[entry.content_hash] = entry

        if entry.destination:
            key = str(entry.destination).lower()
            count = destination_counts.get(key, 0)
            destination_counts[key] = count + 1
            if count:
                entry.destination = entry.destination.with_name(
                    f"{entry.destination.stem}-alt{count + 1}{entry.destination.suffix}"
                )
                entry.reason += f"; alternate solution #{count + 1}"


def print_preview(entries: list[Candidate]) -> None:
    order = {"HIGH": 0, "MEDIUM": 1, "UNRESOLVED": 2}
    entries.sort(key=lambda e: (order.get(e.confidence, 9), e.when, str(e.source).lower()))
    counts: dict[str, int] = {}

    print("\n=== Historical import preview ===")
    for entry in entries:
        counts[entry.status] = counts.get(entry.status, 0) + 1
        tag = entry.status if entry.status != "READY" else entry.confidence
        local_time = entry.when.astimezone().strftime("%Y-%m-%d %H:%M")
        print(f"\n[{tag}] {entry.platform or '?'} | {entry.problem_key} | {local_time}")
        print(f"  source: {entry.source}")
        if entry.destination:
            print(f"  target: {entry.destination.relative_to(ROOT)}")
        print(f"  date:   {entry.date_source}")
        print(f"  why:    {entry.reason}")

    print("\n=== Summary ===")
    for key in ["READY", "UNRESOLVED", "DUPLICATE", "ALREADY-TRACKED"]:
        print(f"{key:16}: {counts.get(key, 0)}")
    print("\nOnly READY entries are imported. Everything else is skipped.")


def write_plan(entries: list[Candidate], roots: list[Path]) -> None:
    payload = {
        "generated_at": datetime.now(tz=timezone.utc).isoformat(),
        "source_roots": [str(p) for p in roots],
        "entries": [
            {
                "source": str(e.source), "source_root": str(e.source_root), "platform": e.platform,
                "problem_key": e.problem_key, "destination": str(e.destination) if e.destination else None,
                "when": e.when.isoformat(), "date_source": e.date_source, "confidence": e.confidence,
                "reason": e.reason, "content_hash": e.content_hash, "status": e.status,
            }
            for e in entries
        ],
    }
    PLAN_FILE.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def load_plan() -> list[Candidate]:
    if not PLAN_FILE.is_file():
        raise SystemExit("No preview plan found. Run 'CP: Preview all historical solutions' first.")
    data = json.loads(PLAN_FILE.read_text(encoding="utf-8"))
    result: list[Candidate] = []
    for raw in data.get("entries", []):
        result.append(Candidate(
            source=Path(raw["source"]), source_root=Path(raw["source_root"]), platform=raw.get("platform"),
            problem_key=raw["problem_key"], destination=Path(raw["destination"]) if raw.get("destination") else None,
            when=datetime.fromisoformat(raw["when"]), date_source=raw["date_source"], confidence=raw["confidence"],
            reason=raw["reason"], content_hash=raw["content_hash"], status=raw["status"],
        ))
    return result


def git_commit(relative: Path, message: str, when: datetime) -> bool:
    run("git", "add", str(relative))
    env = os.environ.copy()
    env["GIT_AUTHOR_DATE"] = when.isoformat()
    env["GIT_COMMITTER_DATE"] = when.isoformat()
    try:
        run("git", "commit", "-m", message, env=env)
        return True
    except subprocess.CalledProcessError:
        return False


def import_plan(entries: list[Candidate], push: bool) -> None:
    ready = [e for e in entries if e.status == "READY" and e.destination is not None]
    if not ready:
        raise SystemExit("The preview contains no importable entries.")

    print_preview(entries)
    print(f"\nAbout to create up to {len(ready)} historical commits.")
    if input("Type IMPORT to continue: ").strip() != "IMPORT":
        raise SystemExit("Cancelled.")

    created = skipped = 0
    for entry in sorted(ready, key=lambda e: e.when):
        if not entry.source.is_file() or sha256_file(entry.source) != entry.content_hash:
            print(f"Skipped changed/missing file: {entry.source}")
            skipped += 1
            continue
        assert entry.destination is not None
        entry.destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(entry.source, entry.destination)
        relative = entry.destination.relative_to(ROOT)
        label = (entry.platform or "unknown").lower().replace(" ", "-")
        if git_commit(relative, f"solve({label}): {entry.problem_key}", entry.when):
            created += 1
            print(f"Committed {relative} [{entry.date_source}]")
        else:
            skipped += 1

    print(f"\nDone: {created} commit(s) created, {skipped} skipped.")
    if push and created:
        run("git", "push")
        print("Pushed to GitHub.")
    elif created:
        print('Review with: git log --date=iso --pretty=format:"%h %ad %s"')
        print("Then publish with: git push")


def main() -> None:
    args = sys.argv[1:]
    if "--configure" in args:
        configure_sources()
        return

    if "--import" in args:
        import_plan(load_plan(), "--push" in args)
        return

    config = load_config()
    roots = source_roots(config)
    if not roots:
        raise SystemExit("No historical folders configured. Run 'CP: Configure historical folders' first.")

    print("Competitive Programming - Multi-folder Historical Preview")
    print("\nSource folders:")
    for root in roots:
        print(f"  - {root}")

    handle = str(config.get("codeforces_handle", "")).strip()
    if handle:
        print(f"\nLoading Codeforces Accepted history for {handle}...")
        cf_by_id, cf_by_title = fetch_codeforces_history(handle)
        print(f"Loaded {len(cf_by_id)} accepted Codeforces problems.")
    else:
        cf_by_id, cf_by_title = {}, {}
        print("\nCodeforces handle is not configured; Codeforces title/date matching will be limited.")

    print("Loading CSES public problem catalog...")
    cses_catalog = fetch_cses_catalog()
    print(f"Loaded {len(cses_catalog)} CSES problem titles.")

    files = collect_files(roots)
    print(f"Scanning {len(files)} source files...")
    entries = [classify(path, root, cf_by_id, cf_by_title, cses_catalog) for path, root in files]
    apply_duplicate_rules(entries)
    print_preview(entries)
    write_plan(entries, roots)

    print(f"\nPreview plan saved locally to {PLAN_FILE.name}.")
    print("Nothing was copied or committed.")
    print("Review MEDIUM and UNRESOLVED entries before importing.")


if __name__ == "__main__":
    main()
