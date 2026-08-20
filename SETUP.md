# Local setup — Windows + VS Code

## 1. Update the local repository

If you already cloned the repository, first pull the latest automation:

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

The email should be associated with your GitHub account if you want the commits to count correctly in your contribution graph.

## 3. Connect your Codeforces handle

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Choose `Tasks: Run Task`.
3. Select `CP: Configure Codeforces handle`.
4. Enter your Codeforces username.

The script validates the handle through the public Codeforces API and stores it locally in `.cpconfig.json`. This file is ignored by Git.

## 4. Archive a new solved problem

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Search for `Tasks: Run Task`.
3. Select `CP: Archive accepted solution`.
4. Enter the platform, problem identifier/title and source-file path.

For Codeforces, the automation checks for an Accepted submission. If found, the commit uses the real Accepted timestamp as `GIT_AUTHOR_DATE` and `GIT_COMMITTER_DATE`.

The commit convention is:

```text
solve(platform): problem
```

To publish immediately, select `CP: Archive and push accepted solution` instead.

## 5. Import old folders and contests

First run:

`CP: Preview historical import`

Enter the folder containing your old solutions. The script scans source files recursively and shows which platform, destination and date would be used.

For Codeforces, when a contest/problem ID can be inferred, the date comes from your first Accepted submission in the Codeforces API. For other platforms, the local file modification time is used as a fallback.

If the preview looks correct, run:

`CP: Import historical solutions`

The script asks for confirmation before creating commits. After reviewing the result, publish them with:

```powershell
git push
```

You can inspect the dates first with:

```powershell
git log --date=iso --pretty=format:"%h %ad %s"
```

## 6. Recommended workflow

During contests or practice sessions, keep temporary files outside the repository or in a separate working folder. Archive only accepted/final solutions. This keeps the public repository clean and makes the Git history useful as a study log.
