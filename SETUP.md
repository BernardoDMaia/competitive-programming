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

## 3. Connect your Codeforces handle

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Choose `Tasks: Run Task`.
3. Select `CP: Configure Codeforces handle`.
4. Enter your Codeforces username.

The handle is validated using the public Codeforces API and saved only in local `.cpconfig.json`.

## 4. Archive a new solved problem

Use `CP: Archive accepted solution` or `CP: Archive and push accepted solution`.

For Codeforces, the automation checks your Accepted history and, when possible, uses the timestamp of your first Accepted submission as the Git author/committer date.

## 5. Configure all old code folders

Run:

`CP: Configure historical folders`

Enter one source folder per line, for example:

```text
C:\Users\Georgia\OneDrive\Área de Trabalho\MARATONASBC
C:\Users\Georgia\...\Treinamento Codeforces
```

Press Enter on an empty line to finish.

Important: the name of the root folder is ignored for platform detection. A folder named `Treinamento Codeforces` may contain AtCoder, CSES, ICPC, USACO Guide and other material without all of it being classified as Codeforces.

The configured paths are stored only in local `.cpconfig.json`.

## 6. Preview the combined historical import

Run:

`CP: Preview all historical solutions`

The scanner walks every configured folder recursively and combines them into one preview.

Detection uses, in order, reliable signals such as:

- explicit subfolders (`atcoder`, `cses`, `codeforces`, `obi`, `beecrowd`, `usaco`);
- ICPC-style contest folders (`NWERC25`, `SWERC26`, `NAQ2024`, `sub2024`, `maratonamineira`);
- direct Codeforces IDs such as `2060A.cpp`;
- exact problem-title matches against your Accepted Codeforces history, so files such as `checkTranscription.cpp` can be recognized;
- exact title matches against the public CSES problem catalog, so files such as `findingperiods.cpp` can be recognized;
- a cautious Codeforces heuristic for generic `A.cpp`, `B.cpp`, etc. only when the contest folder strongly suggests Codeforces and there is one nearby Accepted submission;
- `usacoguide` is treated as a study collection rather than automatically pretending every file came from USACO.

Each result is labeled `HIGH`, `MEDIUM`, `UNRESOLVED`, `DUPLICATE`, or `ALREADY-TRACKED`.

Nothing is copied or committed during preview. The plan is saved locally in `.cp-import-plan.json`, which is ignored by Git.

## 7. Import only after reviewing the preview

If the preview looks correct, run:

`CP: Import previewed historical solutions`

The importer uses the exact previewed plan and requires you to type `IMPORT` before creating commits.

- `READY` items are imported.
- `UNRESOLVED`, `DUPLICATE`, and `ALREADY-TRACKED` items are skipped.
- Codeforces items use the real first-Accepted timestamp whenever matched.
- Other platforms use the file modification date as a clearly identified fallback unless a better source is available.

Then inspect the local history:

```powershell
git log --date=iso --pretty=format:"%h %ad %s"
```

Only after checking it, publish with:

```powershell
git push
```

## 8. Recommended workflow

Keep your original study folders exactly as they are. The importer copies recognized final solutions into this repository; it does not reorganize or delete your original files.

For ambiguous files, prefer leaving them `UNRESOLVED` and handling them later instead of guessing a platform and polluting the public repository.
