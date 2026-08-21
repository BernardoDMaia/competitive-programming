# Automation workflow

- Codeforces: Competitive Companion + CPH -> watcher detects Accepted -> move -> local commit using first Accepted timestamp.
- Other platforms: run `CP: Mark current problem accepted (non-Codeforces)` (recommended keybinding `Ctrl+Alt+A`) -> move -> local commit using command time.
- Weekly publishing: configure `CP: Configure weekly push`; pending local commits are pushed together at the configured weekly schedule while the workspace is running, or on the next workspace opening if the schedule was missed.
