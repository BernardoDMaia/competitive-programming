# Competitive Programming

Repository for archiving my competitive programming solutions and documenting my progress in algorithms, data structures and problem solving.

## Platforms

Solutions are organized by source:

- `Codeforces/`
- `CSES/`
- `USACO/`
- `OBI/`
- `AtCoder/`
- `Beecrowd/`
- `ICPC/`
- `Study/USACO-Guide/` for unresolved study material that came from USACO Guide rather than a confirmed platform

## VS Code workflow

This repository includes local automation in `tools/` and VS Code tasks in `.vscode/tasks.json`.

### Daily workflow

1. Solve a problem locally.
2. Confirm the solution was accepted.
3. Run **Tasks: Run Task** in VS Code.
4. Choose `CP: Archive accepted solution` or `CP: Archive and push accepted solution`.
5. Inform the source platform, problem identifier and solution file.
6. The script copies the solution into the correct folder and creates a standardized Git commit.

For Codeforces, configure your handle once with `CP: Configure Codeforces handle`. When a matching Accepted submission is found, its real submission timestamp is used as the Git author and committer date.

### Multi-folder historical import

Old solutions do not need to be manually reorganized first. Configure all source folders once with:

- `CP: Configure historical folders`

Then run:

- `CP: Preview all historical solutions`
- `CP: Import previewed historical solutions`

The scanner combines multiple folder trees while deliberately ignoring the name of each root folder. This means a root named `Treinamento Codeforces` can safely contain AtCoder, CSES, ICPC, USACO Guide and other material.

Recognition uses explicit subfolders, contest names, Codeforces IDs, exact title matches against the user's Accepted Codeforces history, the public CSES problem catalog, and conservative heuristics for contest files such as `A.cpp` or `B.cpp`.

Every candidate receives a confidence/status label:

- `HIGH` — reliable match;
- `MEDIUM` — useful but should be reviewed;
- `UNRESOLVED` — not imported automatically;
- `DUPLICATE` — identical source already found in another configured folder;
- `ALREADY-TRACKED` — identical source code is already in this repository.

Preview never creates commits. The importer only acts on the saved preview plan and asks for explicit confirmation first.

For dates:

- **Codeforces:** matched problems use the real first-Accepted timestamp from the Codeforces API.
- **Other platforms:** the local file modification timestamp is used as a clearly identified fallback unless a better source is available.

### Commit convention

Examples:

```text
solve(codeforces): 2060A
solve(cses): 1076
solve(usaco): Lights Out
solve(icpc): A
add(template): dijkstra
```

## Featured solution

### [USACO — Lights Out](USACO/2016-January-Gold/lights-out.cpp)

My solution for **USACO 2016 January Gold — Problem 3: Lights Out**. The approach encodes the polygon path using edge lengths and turn directions, then uses double polynomial hashing to compare path signatures efficiently.

## Notes

This repository is meant to be a technical record of solved problems and study progress. Problem statements belong to their respective platforms; only my own source code and notes are stored here.
