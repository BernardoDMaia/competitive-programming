# Competitive Programming

Repository for my competitive-programming solutions, study material and reusable templates.

## Platforms

Completed solutions are organized by source:

- `Codeforces/`
- `AtCoder/`
- `CSES/`
- `USACO/`
- `OBI/`
- `Beecrowd/`
- `SPOJ/`
- `Kattis/`
- `ICPC/`
- `Study/` for topic-based practice whose original platform is not confirmed
- `Templates/` for reusable algorithms and data structures

## Daily workflow: Competitive Companion + CPH + Git

The repository is designed to work with **Competitive Companion** in the browser and **Competitive Programming Helper (CPH)** in VS Code.

### Codeforces — fully automatic after Accepted

1. Send a Codeforces problem to CPH with Competitive Companion.
2. Solve and submit it normally.
3. `CP: Codeforces Accepted watcher` runs in the background while this workspace is open.
4. When the configured Codeforces account receives `Accepted`, the watcher automatically:
   - detects the problem from CPH metadata;
   - moves the source to `Codeforces/<contest>/<problem>.cpp`;
   - keeps the CPH metadata associated with the moved file;
   - creates one **local** Git commit;
   - uses the timestamp of the **first Accepted submission** as the Git author/committer date.
5. No immediate push is performed.

Example:

```text
2257F2.cpp
    -> Accepted detected
    -> Codeforces/2257/2257F2.cpp
    -> solve(codeforces): 2257F2
```

### Other platforms — one-key Accepted confirmation

For AtCoder, CSES, USACO, OBI, Beecrowd, SPOJ, Kattis and other non-Codeforces problems, keep the CPH-created source file active and run:

- `CP: Mark current problem accepted (non-Codeforces)`

That command means **the judge returned Accepted**. It automatically detects the platform from CPH metadata, moves the source into the correct repository folder and creates a local commit using the **exact time the command was triggered**.

A convenient VS Code user keybinding is:

```json
{
  "key": "ctrl+alt+a",
  "command": "workbench.action.tasks.runTask",
  "args": "CP: Mark current problem accepted (non-Codeforces)"
}
```

### Weekly publishing

Commits accumulate locally during the week. Configure the publication schedule once with:

- `CP: Configure weekly push`

The Codeforces watcher checks the schedule in the background. When the configured weekly time is due, it pushes every pending commit on local `main` to `origin/main`. If the workspace was closed at the scheduled time, the push is performed the next time the workspace is opened.

The weekly publisher refuses to push if local `main` is behind `origin/main`.

To publish early, run:

- `CP: Push pending solutions now`

### Commit dates

- **Codeforces:** first Accepted timestamp returned by the Codeforces API.
- **Other platforms:** exact time `CP: Mark current problem accepted` is triggered.
- **Historical import:** file modification time when no better timestamp is available.

Examples:

```text
solve(codeforces): 2257F2
solve(atcoder): ABC463-D
solve(cses): 1076
solve(usaco): 832
solve(spoj): GCDEX
```

## One-time setup

See [`SETUP.md`](SETUP.md). The important tasks are:

```text
CP: Configure Codeforces handle
CP: Configure weekly push
CP: Codeforces Accepted watcher
CP: Mark current problem accepted (non-Codeforces)
CP: Push pending solutions now
```

## Historical solutions

Older folders can be imported without manually reorganizing them first:

```text
CP: Configure historical folders
CP: Preview all historical solutions
CP: Import previewed historical solutions
```

The importer combines multiple folder trees, detects platforms and contests conservatively, separates study material, detects duplicates and previews everything before creating commits.

## Featured solution

### [USACO — Lights Out](USACO/2016-January-Gold/lights-out.cpp)

My solution for **USACO 2016 January Gold — Problem 3: Lights Out**. The approach encodes the polygon path using edge lengths and turn directions, then uses double polynomial hashing to compare path signatures efficiently.

## Notes

This repository is a technical record of solved problems and study progress. Problem statements belong to their respective platforms; only my own source code, templates and notes are stored here.
