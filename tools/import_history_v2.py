from __future__ import annotations

import difflib
import os
import re
import shutil
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

import import_history as base


TOPIC_FOLDERS = {
    "hashing": "Hashing",
    "combinatorics": "Combinatorics",
    "divisibility": "Divisibility",
    "modulararithmetic": "Modular-Arithmetic",
    "bfs": "BFS",
    "dp": "Dynamic-Programming",
    "segtree": "Segment-Tree",
    "dsu": "DSU",
    "toposort": "Topological-Sort",
    "problemset": "Problemset",
}

KNOWN_USACO_TITLES = {
    "lightsout": "Lights-Out",
    "bovinegenomics": "Bovine-Genomics",
    "censoring": "Censoring",
    "juststalling": "Just-Stalling",
    "mooroute": "Moo-Route",
    "cowpatibilities": "Cowpatibility",
    "cowpatibility": "Cowpatibility",
    "mootube": "MooTube",
}

KNOWN_ATCODER = {
    "divgame": ("ABC169", "D-Div-Game"),
    "frog1": ("DP", "A-Frog-1"),
    "frog2": ("DP", "B-Frog-2"),
}

KNOWN_SPOJ = {
    "gcdex": "GCDEX",
    "marbles": "MARBLES",
}


def compact_title(text: str) -> str:
    stem = Path(text).stem
    stem = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", stem)
    stem = re.sub(r"(?<=[A-Za-z])(?=\d)|(?<=\d)(?=[A-Za-z])", " ", stem)
    stem = stem.replace("_", " ").replace("-", " ").replace(".", " ")
    words = re.findall(r"[a-z0-9]+", stem.lower())
    aliases = {
        "mod": "modulo",
        "coeficient": "coefficient",
        "coeficients": "coefficients",
        "binominal": "binomial",
    }
    words = [aliases.get(w, w) for w in words]
    return "".join(words)


def safe_slug(text: str) -> str:
    return "-".join(re.findall(r"[A-Za-z0-9]+", text)) or "problem"


def unique_compact_cf(path: Path, cf_by_title) -> base.CodeforcesProblem | None:
    key = compact_title(path.stem)
    matches: list[base.CodeforcesProblem] = []
    for normalized, problems in cf_by_title.items():
        if compact_title(normalized) == key:
            matches.extend(problems)
    return matches[0] if len(matches) == 1 else None


def fuzzy_cf(path: Path, cf_by_title) -> base.CodeforcesProblem | None:
    key = compact_title(path.stem)
    if len(key) < 7:
        return None
    scored = []
    for normalized, problems in cf_by_title.items():
        if len(problems) != 1:
            continue
        other = compact_title(normalized)
        if not other:
            continue
        if key in other or other in key:
            ratio = 0.97
        else:
            ratio = difflib.SequenceMatcher(None, key, other).ratio()
        scored.append((ratio, problems[0]))
    scored.sort(key=lambda x: x[0], reverse=True)
    if not scored:
        return None
    best_ratio, best = scored[0]
    second = scored[1][0] if len(scored) > 1 else 0.0
    if best_ratio >= 0.90 and best_ratio - second >= 0.04:
        return best
    return None


def compact_cses(path: Path, catalog) -> tuple[str, str] | None:
    key = compact_title(path.stem)
    exact = []
    for normalized, item in catalog.items():
        if compact_title(normalized) == key:
            exact.append(item)
    if len(exact) == 1:
        return exact[0]

    scored = []
    for normalized, item in catalog.items():
        other = compact_title(normalized)
        ratio = difflib.SequenceMatcher(None, key, other).ratio()
        scored.append((ratio, item))
    scored.sort(key=lambda x: x[0], reverse=True)
    if scored:
        best_ratio, best = scored[0]
        second = scored[1][0] if len(scored) > 1 else 0.0
        if best_ratio >= 0.92 and best_ratio - second >= 0.05:
            return best
    return None


def cf_id_anywhere(path: Path, cf_by_id) -> base.CodeforcesProblem | None:
    stem = re.sub(r"[^A-Za-z0-9]", "", path.stem)
    match = re.search(r"(\d{3,6})([A-Za-z][A-Za-z0-9]*)$", stem)
    if not match:
        return None
    return cf_by_id.get((int(match.group(1)), match.group(2).upper()))


def first_matching_part(parts: list[str], predicate) -> tuple[int, str] | None:
    for i, part in enumerate(parts[:-1]):
        if predicate(part):
            return i, part
    return None


def fallback_candidate(path: Path, source_root: Path, cf_by_id, cf_by_title, cses_catalog) -> base.Candidate:
    parts = base.rel_parts(path, source_root)
    when = datetime.fromtimestamp(path.stat().st_mtime, tz=timezone.utc)
    content_hash = base.sha256_file(path)
    suffix = path.suffix.lower()

    problem = cf_id_anywhere(path, cf_by_id) or unique_compact_cf(path, cf_by_title) or fuzzy_cf(path, cf_by_title)
    if problem:
        dest = base.ROOT / "Codeforces" / str(problem.contest_id) / f"{problem.contest_id}{problem.index}{suffix}"
        return base.Candidate(path, source_root, "Codeforces", f"{problem.contest_id}{problem.index}", dest,
                              problem.first_ac, "Codeforces first Accepted", "HIGH",
                              f"matched Codeforces history by filename/title ('{problem.name}')", content_hash)

    cses = compact_cses(path, cses_catalog)
    if cses:
        task_id, title = cses
        dest = base.ROOT / "CSES" / f"{task_id}-{safe_slug(title)}{suffix}"
        return base.Candidate(path, source_root, "CSES", task_id, dest, when, "file modified time", "HIGH",
                              f"matched CSES title '{title}'", content_hash)

    key = compact_title(path.stem)
    if key in KNOWN_USACO_TITLES:
        title = KNOWN_USACO_TITLES[key]
        dest = base.ROOT / "USACO" / "By-Title" / f"{title}{suffix}"
        return base.Candidate(path, source_root, "USACO", title, dest, when, "file modified time", "HIGH",
                              "known USACO problem title", content_hash)

    if key in KNOWN_ATCODER:
        contest, title = KNOWN_ATCODER[key]
        dest = base.ROOT / "AtCoder" / contest / f"{title}{suffix}"
        return base.Candidate(path, source_root, "AtCoder", title, dest, when, "file modified time", "HIGH",
                              "known AtCoder problem title", content_hash)

    if key in KNOWN_SPOJ:
        title = KNOWN_SPOJ[key]
        dest = base.ROOT / "SPOJ" / f"{title}{suffix}"
        return base.Candidate(path, source_root, "SPOJ", title, dest, when, "file modified time", "HIGH",
                              "known SPOJ problem code/title", content_hash)

    template = first_matching_part(parts, lambda p: p.lower() == "templates")
    if template:
        i, _ = template
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Templates" / tail
        return base.Candidate(path, source_root, "Template", path.stem, dest, when, "file modified time", "HIGH",
                              "template folder", content_hash)

    contest = first_matching_part(
        parts,
        lambda p: bool(re.match(r"^contest(?:[._-].+|[A-Za-z0-9].*)$", p, re.I)),
    )
    if contest:
        i, folder = contest
        folder_slug = safe_slug(folder)
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Contests" / folder_slug / tail
        return base.Candidate(path, source_root, "Contest", path.stem, dest, when, "file modified time", "HIGH",
                              f"preserved local contest grouping '{folder}' without asserting an external platform", content_hash)

    named_contest = first_matching_part(parts, lambda p: p.lower() in {"mfp", "mfpfinal", "seletiva"})
    if named_contest:
        i, folder = named_contest
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Contests" / safe_slug(folder) / tail
        return base.Candidate(path, source_root, "Contest", path.stem, dest, when, "file modified time", "MEDIUM",
                              f"local contest/training grouping '{folder}'", content_hash)

    div2 = first_matching_part(parts, lambda p: p.lower() == "div2")
    if div2:
        i, _ = div2
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Study" / "Codeforces" / "Div2-Unidentified" / tail
        return base.Candidate(path, source_root, "Study", path.stem, dest, when, "file modified time", "MEDIUM",
                              "Codeforces-style Div2 folder but exact contest could not be proved", content_hash)

    knowwho = first_matching_part(parts, lambda p: p.lower() == "knowwho")
    if knowwho:
        i, _ = knowwho
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Study" / "KnowWho" / tail
        return base.Candidate(path, source_root, "Study", path.stem, dest, when, "file modified time", "MEDIUM",
                              "study collection; source platform unresolved", content_hash)

    topic = first_matching_part(parts, lambda p: re.sub(r"[^a-z0-9]", "", p.lower()) in TOPIC_FOLDERS)
    if topic:
        i, folder = topic
        topic_key = re.sub(r"[^a-z0-9]", "", folder.lower())
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Study" / "Topics" / TOPIC_FOLDERS[topic_key] / tail
        return base.Candidate(path, source_root, "Study", path.stem, dest, when, "file modified time", "MEDIUM",
                              f"topic folder '{folder}'; original platform unresolved", content_hash)

    misc = first_matching_part(parts, lambda p: p.lower() == "outros")
    if misc:
        i, _ = misc
        tail = Path(*parts[i + 1 :])
        dest = base.ROOT / "Study" / "Misc" / tail
        return base.Candidate(path, source_root, "Study", path.stem, dest, when, "file modified time", "MEDIUM",
                              "miscellaneous study folder; original platform unresolved", content_hash)

    return base.Candidate(path, source_root, None, path.stem, None, when, "file modified time", "UNRESOLVED",
                          "no reliable platform/problem or safe local grouping", content_hash, status="UNRESOLVED")


def classify_v2(path: Path, source_root: Path, cf_by_id, cf_by_title, cses_catalog) -> base.Candidate:
    first = base.classify(path, source_root, cf_by_id, cf_by_title, cses_catalog)
    if first.status != "UNRESOLVED":
        return first
    return fallback_candidate(path, source_root, cf_by_id, cf_by_title, cses_catalog)


def commit_message(entry: base.Candidate) -> str:
    if entry.platform == "Template":
        return f"add(template): {entry.problem_key}"
    if entry.platform == "Study":
        return f"study: {entry.problem_key}"
    if entry.platform == "Contest":
        return f"solve(contest): {entry.problem_key}"
    label = (entry.platform or "unknown").lower().replace(" ", "-")
    return f"solve({label}): {entry.problem_key}"


def import_plan(entries: list[base.Candidate], push: bool) -> None:
    ready = [e for e in entries if e.status == "READY" and e.destination is not None]
    if not ready:
        raise SystemExit("The preview contains no importable entries.")

    base.print_preview(entries)
    print(f"\nAbout to create up to {len(ready)} historical commits.")
    if input("Type IMPORT to continue: ").strip() != "IMPORT":
        raise SystemExit("Cancelled.")

    created = skipped = 0
    for entry in sorted(ready, key=lambda e: e.when):
        if not entry.source.is_file() or base.sha256_file(entry.source) != entry.content_hash:
            print(f"Skipped changed/missing file: {entry.source}")
            skipped += 1
            continue
        assert entry.destination is not None
        entry.destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(entry.source, entry.destination)
        relative = entry.destination.relative_to(base.ROOT)
        if base.git_commit(relative, commit_message(entry), entry.when):
            created += 1
            print(f"Committed {relative} [{entry.date_source}]")
        else:
            skipped += 1

    print(f"\nDone: {created} commit(s) created, {skipped} skipped.")
    if push and created:
        base.run("git", "push")
        print("Pushed to GitHub.")
    elif created:
        print('Review with: git log --date=iso --pretty=format:"%h %ad %s"')
        print("Then publish with: git push")


def main() -> None:
    args = sys.argv[1:]
    if "--configure" in args:
        base.configure_sources()
        return
    if "--import" in args:
        import_plan(base.load_plan(), "--push" in args)
        return

    config = base.load_config()
    roots = base.source_roots(config)
    if not roots:
        raise SystemExit("No historical folders configured. Run 'CP: Configure historical folders' first.")

    print("Competitive Programming - Historical Preview v2")
    print("\nSource folders:")
    for root in roots:
        print(f"  - {root}")

    handle = str(config.get("codeforces_handle", "")).strip()
    if handle:
        print(f"\nLoading Codeforces Accepted history for {handle}...")
        cf_by_id, cf_by_title = base.fetch_codeforces_history(handle)
        print(f"Loaded {len(cf_by_id)} accepted Codeforces problems.")
    else:
        cf_by_id, cf_by_title = {}, {}
        print("\nCodeforces handle is not configured; Codeforces matching will be limited.")

    print("Loading CSES public problem catalog...")
    cses_catalog = base.fetch_cses_catalog()
    print(f"Loaded {len(cses_catalog)} CSES problem titles.")

    files = base.collect_files(roots)
    print(f"Scanning {len(files)} source files...")
    entries = [classify_v2(path, root, cf_by_id, cf_by_title, cses_catalog) for path, root in files]
    base.apply_duplicate_rules(entries)
    base.print_preview(entries)
    base.write_plan(entries, roots)

    print(f"\nPreview plan saved locally to {base.PLAN_FILE.name}.")
    print("Nothing was copied or committed.")
    print("HIGH = identified source/problem or safe explicit grouping.")
    print("MEDIUM = safe archive location, but original platform/problem may still be unresolved.")


if __name__ == "__main__":
    main()
