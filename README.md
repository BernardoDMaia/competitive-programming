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

This repository includes a small local automation in `tools/archive_solution.py` and VS Code tasks in `.vscode/tasks.json`.

The intended workflow is:

1. Solve a problem locally.
2. Confirm the solution was accepted.
3. Run **Tasks: Run Task** in VS Code.
4. Choose `CP: Archive accepted solution`.
5. Inform the source platform, problem identifier and solution file.
6. The script copies the solution into the correct folder and prepares a standardized Git commit.

For Codeforces, you can optionally set the environment variable `CODEFORCES_HANDLE`; the script will check your recent submissions through the public Codeforces API before archiving the file.

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
