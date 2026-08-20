# Local setup — Windows + VS Code

## 1. Clone the repository

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

## 3. Optional: connect your Codeforces handle

Set your Codeforces handle once in Windows PowerShell:

```powershell
setx CODEFORCES_HANDLE "YOUR_HANDLE"
```

Close and reopen VS Code after running `setx`.

When this variable is configured, the archive script checks your most recent Codeforces submissions before archiving a solution.

## 4. Archive a solved problem

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Search for `Tasks: Run Task`.
3. Select `CP: Archive accepted solution`.
4. Enter the platform, problem identifier/title and source-file path.

The script places the file in the appropriate platform folder, stages only that file and creates a commit using the convention:

```text
solve(platform): problem
```

To publish immediately, select `CP: Archive and push accepted solution` instead.

## 5. Recommended workflow

During a contest or practice session, keep temporary files outside the repository or in a separate working folder. Archive only accepted/final solutions. This keeps the public repository clean and makes the Git history useful as a study log.
