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
- `SPOJ/`
- `Kattis/`
- `Study/USACO-Guide/` for study material whose original platform is not confirmed

## VS Code + Competitive Companion + CPH workflow

This repository is configured to work with **Competitive Companion** in the browser and **Competitive Programming Helper (CPH)** in VS Code.

### Daily workflow

1. Open the problem in the browser.
2. Send it with Competitive Companion.
3. CPH creates the temporary source file in the workspace and loads the sample tests.
4. Solve and test with CPH (`Ctrl+Alt+B`).
5. After the solution is accepted, keep that source file active and run:
   - `CP: Finish current problem`, or
   - `CP: Finish current problem and push`.
6. The script reads the CPH `.prob` metadata, detects the platform and problem, moves the source to the correct folder, preserves the CPH metadata for the new path, creates a standardized Git commit and optionally pushes it.

Examples of automatic destinations:

```text
Codeforces/2257/2257F2.cpp
AtCoder/ABC463/D.cpp
CSES/1076-Sliding-Window-Median.cpp
USACO/2016-January-Gold/lights-out.cpp
Beecrowd/1001.cpp
SPOJ/GCDEX.cpp
```

### Commit dates

- **Codeforces:** the script requires an Accepted submission for the configured handle and uses the timestamp of the first Accepted submission.
- **Other platforms:** the source file modification timestamp is used.

Configure the Codeforces handle once with:

- `CP: Configure Codeforces handle`

### Commit convention

Examples:

```text
solve(codeforces): 2257F2
solve(atcoder): ABC463-D
solve(cses): 1076
solve(usaco): 832
solve(spoj): GCDEX
```

## Historical solutions

Older folders can still be imported without manual reorganization.

Configure the folders once with:

- `CP: Configure historical folders`

Then run:

- `CP: Preview all historical solutions`
- `CP: Import previewed historical solutions`

The scanner combines multiple folder trees, detects platforms and contests when possible, separates study material conservatively, detects duplicates, and previews everything before creating commits.

For historical dates:

- **Codeforces:** matched problems use the real first-Accepted timestamp from the Codeforces API.
- **Other platforms:** the local file modification timestamp is used as a fallback.

## Featured solution

### [USACO — Lights Out](USACO/2016-January-Gold/lights-out.cpp)

My solution for **USACO 2016 January Gold — Problem 3: Lights Out**. The approach encodes the polygon path using edge lengths and turn directions, then uses double polynomial hashing to compare path signatures efficiently.

## Notes

This repository is a technical record of solved problems and study progress. Problem statements belong to their respective platforms; only my own source code, templates and notes are stored here.
