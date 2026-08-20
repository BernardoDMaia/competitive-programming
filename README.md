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
- `Uncategorized/`

## VS Code workflow

This repository includes local automation in `tools/` and VS Code tasks in `.vscode/tasks.json`.

### Daily workflow

1. Solve a problem locally.
2. Confirm the solution was accepted.
3. Run **Tasks: Run Task** in VS Code.
4. Choose `CP: Archive accepted solution` or `CP: Archive and push accepted solution`.
5. Inform the source platform, problem identifier and solution file.
6. The script copies the solution into the correct folder and creates a standardized Git commit.

For Codeforces, configure your handle once with the task `CP: Configure Codeforces handle`. The script then checks the public Codeforces API before archiving a solution. When an Accepted submission is found, its real submission timestamp is used as the Git author and committer date.

### Historical solutions

Older folders can be imported with `tools/import_history.py` or the VS Code tasks:

- `CP: Preview historical import`
- `CP: Import historical solutions`

The importer scans old source files recursively and creates one commit per solution.

- **Codeforces:** when the problem can be identified, the first Accepted submission timestamp from the Codeforces API is used.
- **Other platforms:** the local file modification timestamp is used as a fallback and is clearly shown in the preview before any commit is created.

This keeps the public history tied to real evidence instead of invented dates.

### Commit convention

Examples:

```text
solve(codeforces): 2060A
solve(cses): Tree Matching
solve(usaco): Lights Out
add(template): dijkstra
```

## Featured solution

### [USACO — Lights Out](USACO/2016-January-Gold/lights-out.cpp)

My solution for **USACO 2016 January Gold — Problem 3: Lights Out**. The approach encodes the polygon path using edge lengths and turn directions, then uses double polynomial hashing to compare path signatures efficiently.

## Notes

This repository is meant to be a technical record of solved problems and study progress. Problem statements belong to their respective platforms; only my own source code and notes are stored here.
