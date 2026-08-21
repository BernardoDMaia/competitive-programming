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

Open the repository root in VS Code. When you send a problem from the browser, CPH creates the temporary source file in the workspace and stores its problem metadata in a `.cph` directory. These metadata files are ignored by Git.

Recommended daily flow:

1. Send the problem with Competitive Companion.
2. Solve it in the file opened by CPH.
3. Run sample tests with `Ctrl+Alt+B`.
4. Submit the solution to the platform.
5. After Accepted, keep the solution file active.
6. Press `Ctrl+Shift+P` → `Tasks: Run Task`.
7. Choose `CP: Finish current problem and push`.

The finish task automatically reads the CPH metadata, identifies the platform from the problem URL, moves the file to the repository structure, updates the CPH metadata to the new path, commits it, and pushes it.

Supported automatic routing includes Codeforces, AtCoder, CSES, USACO, OBI, Beecrowd, SPOJ, Kattis and ICPC-style metadata. Unknown sources are kept under `Other/` instead of being mislabeled.

For Codeforces, the finish task requires an Accepted submission and uses the timestamp of the first Accepted as the commit date. Other platforms use the file modification timestamp.

## 4. Connect your Codeforces handle

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Choose `Tasks: Run Task`.
3. Select `CP: Configure Codeforces handle`.
4. Enter your Codeforces username.

The handle is validated using the public Codeforces API and saved only in local `.cpconfig.json`.

## 5. Manual archive fallback

If a file was not created by Competitive Companion/CPH, use `CP: Archive accepted solution` or `CP: Archive and push accepted solution`.

## 6. Configure all old code folders

Run:

`CP: Configure historical folders`

Enter one source folder per line, for example:

```text
C:\Users\Georgia\OneDrive\Área de Trabalho\MARATONASBC
C:\Users\Georgia\...\Treinamento Codeforces
```

Press Enter on an empty line to finish.

The configured paths are stored only in local `.cpconfig.json`.

## 7. Preview the combined historical import

Run:

`CP: Preview all historical solutions`

The scanner walks every configured folder recursively and combines them into one preview. It identifies platforms and contests conservatively, detects duplicates, and keeps ambiguous study material separated instead of guessing.

Nothing is copied or committed during preview. The plan is saved locally in `.cp-import-plan.json`, which is ignored by Git.

## 8. Import only after reviewing the preview

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

## 9. Recommended study organization

Use platform folders for completed problems and `Study/` for topic-based practice. Keep reusable snippets in `Templates/` and avoid committing temporary binaries or CPH metadata.
