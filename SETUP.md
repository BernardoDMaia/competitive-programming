# Local setup — Windows + VS Code

## 1. Update the repository

```powershell
git status
git pull
```

Open the repository root in VS Code.

## 2. Requirements

These commands should work in the VS Code terminal:

```powershell
python --version
git --version
g++ --version
```

Check the Git identity as well:

```powershell
git config user.name
git config user.email
```

The email should be associated with your GitHub account.

## 3. Competitive Companion + CPH

Install Competitive Companion in the browser and Competitive Programming Helper (CPH) in VS Code.

When a problem is sent from the browser, CPH creates the source file and local `.prob` metadata under `.cph/`. Those metadata files are ignored by Git but are used by the automation to recover the problem URL and destination.

## 4. Configure Codeforces once

Run:

`Ctrl+Shift+P` → `Tasks: Run Task` → `CP: Configure Codeforces handle`

Enter your Codeforces handle. It is validated through the public Codeforces API and saved only in `.cpconfig.json`.

## 5. Configure the weekly push once

Run:

`Ctrl+Shift+P` → `Tasks: Run Task` → `CP: Configure weekly push`

Choose the weekday and time. Defaults are Sunday at 20:00.

This only configures local behavior. Commits are pushed automatically by the watcher when the workspace is running. If VS Code was closed at the scheduled moment, the next workspace opening performs the overdue push.

## 6. Allow the Codeforces watcher to start automatically

The task `CP: Codeforces Accepted watcher` is configured with `runOn: folderOpen`.

The first time VS Code asks about automatic tasks, allow them for this trusted repository. If it does not prompt automatically, use:

`Ctrl+Shift+P` → `Tasks: Manage Automatic Tasks in Folder` → allow automatic tasks.

You can also start it manually at any time:

`Ctrl+Shift+P` → `Tasks: Run Task` → `CP: Codeforces Accepted watcher`

Only one watcher instance is allowed at a time.

## 7. Codeforces daily flow — no task after AC

1. Open a Codeforces problem in the browser.
2. Send it with Competitive Companion.
3. Solve it in the file opened by CPH.
4. Test with CPH (`Ctrl+Alt+B`).
5. Submit to Codeforces.
6. When Codeforces returns Accepted, do nothing else.

Within about 45 seconds the watcher sees the Accepted submission, moves the file into:

```text
Codeforces/<contest>/<problem>.cpp
```

and creates a local commit such as:

```text
solve(codeforces): 2257F2
```

The commit uses the timestamp of the first Accepted submission on Codeforces.

## 8. Non-Codeforces flow — one shortcut after AC

For AtCoder, CSES, USACO, OBI, Beecrowd, SPOJ, Kattis and other sources, after the online judge returns Accepted keep the problem file active and run:

`CP: Mark current problem accepted (non-Codeforces)`

The command detects the platform from CPH metadata, moves the source, updates the CPH association and creates one local commit using the exact time you triggered the command.

### Recommended keyboard shortcut

Open:

`Ctrl+Shift+P` → `Preferences: Open Keyboard Shortcuts (JSON)`

Add:

```json
{
  "key": "ctrl+alt+a",
  "command": "workbench.action.tasks.runTask",
  "args": "CP: Mark current problem accepted (non-Codeforces)"
}
```

After that, `Ctrl+Alt+A` means: **this non-Codeforces problem was Accepted; organize and commit it now**.

## 9. Weekly publishing

During the week, accepted solutions are committed locally but are not pushed immediately.

Check pending commits:

```powershell
git rev-list --count origin/main..HEAD
git log origin/main..HEAD --oneline
```

At the configured weekly time, the watcher automatically executes the equivalent of:

```powershell
git fetch origin main
git push origin main
```

but only if local `main` is not behind `origin/main`.

To publish early:

`CP: Push pending solutions now`

## 10. Historical solutions

The existing historical importer remains available:

```text
CP: Configure historical folders
CP: Preview all historical solutions
CP: Import previewed historical solutions
```

Review the preview before importing old files.

## 11. Recommended routine

Normal Codeforces session:

```text
Competitive Companion → CPH → solve → submit → Accepted
                                      ↓
                           watcher organizes + commits
```

Other platforms:

```text
Competitive Companion → CPH → solve → submit → Accepted → Ctrl+Alt+A
```

Weekend:

```text
pending local commits → automatic weekly push → GitHub
```
