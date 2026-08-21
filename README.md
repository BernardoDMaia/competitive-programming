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
3. CPH creates the source file in the workspace and loads the sample tests.
4. Solve and test with CPH (`Ctrl+Alt+B`).
5. Submit the solution to the platform.

For a **non-Codeforces** problem that receives Accepted, keep the source file active and run:

- `CP: Mark current problem accepted (non-Codeforces)`

That command is itself the Accepted confirmation: it reads the CPH metadata, detects the platform/problem, moves the source into the correct folder, preserves the CPH association and creates a **local commit using the exact time the command was triggered**. It does not push.

This makes it possible to accumulate solved problems locally during the week and publish all pending commits together later with a single `git push`.

Examples of automatic destinations:

```text
Codeforces/2257/2257F2.cpp
AtCoder/ABC463/D.cpp
CSES/1076-Sliding-Window-Median.cpp
USACO/2016-January-Gold/lights-out.cpp
Beecrowd/1001.cpp
SPOJ/GCDEX.cpp
```

### Codeforces

The existing `CP: Finish current problem` task verifies an Accepted submission for the configured Codeforces handle and uses the timestamp of the first Accepted submission as the commit date. The repository is structured so this verification can also be used by an automatic Accepted watcher.

Configure the Codeforces handle once with:

- `CP: Configure Codeforces handle`

### Commit dates

- **Codeforces:** first Accepted timestamp from the Codeforces API.
- **Non-Codeforces manual Accepted command:** exact time the command/shortcut is triggered.
- **Historical imports:** local file modification time when no better platform timestamp is available.

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
