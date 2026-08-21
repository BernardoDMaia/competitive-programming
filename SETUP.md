# Local setup — Windows + VS Code

## 1. Update the local repository

If you already cloned the repository:

```powershell
git status
git pull
```

If you have not cloned it yet:

```powershell
git clone https://github.com/BernardoDMaia/competitive-programming.git
cd competitive-programming
code .
```

## 2. Requirements

Make sure these commands work in the VS Code terminal:

```powershell
python --version
git --version
g++ --version
```

Also check the Git identity used for commits:

```powershell
git config user.name
git config user.email
```

The email should be associated with your GitHub account if you want the commits to appear correctly in your contribution graph.

## 3. Competitive Companion + CPH

Install Competitive Companion in the browser and Competitive Programming Helper (CPH) in VS Code.

Open the repository root in VS Code. When you send a problem from the browser, CPH creates the source file in the workspace and stores its problem metadata in a `.cph` directory. These metadata files are ignored by Git.

Recommended daily flow:

1. Send the problem with Competitive Companion.
2. Solve it in the file opened by CPH.
3. Run sample tests with `Ctrl+Alt+B`.
4. Submit the solution to the platform.
5. After Accepted, keep the solution file active.

### Non-Codeforces Accepted shortcut

For AtCoder, CSES, USACO, OBI, Beecrowd, SPOJ, Kattis and other non-Codeforces sources, run:

`CP: Mark current problem accepted (non-Codeforces)`

The command immediately:

- reads the CPH metadata for the active file;
- detects the platform/problem from the problem URL;
- moves the source into the repository structure;
- rewrites the CPH metadata for the new source path;
- creates one local Git commit;
- uses the exact time the command was triggered as author/committer date;
- does **not** push.

The shortcut itself is treated as your confirmation that the judge returned Accepted.

### Assign a keyboard shortcut

VS Code task shortcuts are user-level settings. Open:

`Ctrl+Shift+P` → `Preferences: Open Keyboard Shortcuts (JSON)`

Add an entry such as:

```json
{
  "key": "ctrl+alt+a",
  "command": "workbench.action.tasks.runTask",
  "args": "CP: Mark current problem accepted (non-Codeforces)"
}
```

After that, with a CPH problem file active, `Ctrl+Alt+A` means: **this problem was Accepted; organize and commit it locally now**.

If that shortcut conflicts with another command on your machine, choose another key combination.

## 4. Codeforces

Configure your handle once:

1. Press `Ctrl+Shift+P`.
2. Choose `Tasks: Run Task`.
3. Select `CP: Configure Codeforces handle`.
4. Enter your Codeforces username.

The handle is validated using the public Codeforces API and saved only in local `.cpconfig.json`.

The existing `CP: Finish current problem` task verifies Codeforces Accepted status and uses the first Accepted timestamp as the commit date.

## 5. Pending commits and weekly publishing

Every Accepted command creates a normal local Git commit. You can accumulate many during the week without pushing.

Check how many are pending:

```powershell
git rev-list --count origin/main..HEAD
```

List them:

```powershell
git log origin/main..HEAD --oneline
```

A later `git push origin main` publishes all pending commits at once while preserving each commit's own date.

## 6. Manual archive fallback

If a file was not created by Competitive Companion/CPH, use `CP: Archive accepted solution` or `CP: Archive and push accepted solution`.

## 7. Configure all old code folders

Run:

`CP: Configure historical folders`

Enter one source folder per line, for example:

```text
C:\Users\Georgia\OneDrive\Área de Trabalho\MARATONASBC
C:\Users\Georgia\...\Treinamento Codeforces
```

Press Enter on an empty line to finish.

The configured paths are stored only in local `.cpconfig.json`.

## 8. Preview the combined historical import

Run:

`CP: Preview all historical solutions`

The scanner walks every configured folder recursively and combines them into one preview. It identifies platforms and contests conservatively, detects duplicates, and keeps ambiguous study material separated instead of guessing.

Nothing is copied or committed during preview. The plan is saved locally in `.cp-import-plan.json`, which is ignored by Git.

## 9. Import only after reviewing the preview

If the preview looks correct, run:

`CP: Import previewed historical solutions`

The importer requires you to type `IMPORT` before creating commits.

Then inspect the local history:

```powershell
git log --date=iso --pretty=format:"%h %ad %s"
```

Publish with:

```powershell
git push
```

## 10. Recommended study organization

Use platform folders for completed problems and `Study/` for topic-based practice. Keep reusable snippets in `Templates/` and avoid committing temporary binaries or CPH metadata.
