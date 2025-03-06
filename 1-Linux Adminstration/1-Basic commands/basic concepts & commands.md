## Unwrapping Linux

### File System Layout in Linux

Linux follows a **unified hierarchy**, where everything is part of a single directory tree. Devices, files, and directories are all structured under the **root directory (`/`)**.

### Linux File-System Hierarchy

The Linux file system consists of several key directories, each serving a specific purpose:

- `/` : Root directory, the starting point of the hierarchy.
- `/bin` : Essential system binaries.
- `/etc` : System configuration files.
- `/home` : User home directories.
- `/var` : Variable data (logs, cache, etc.).
- `/mnt` : Mount points for temporary file systems.
- `/tmp` : "Temporary files" files that are typically created for backup, storage or cache purposes by a program or operating system.
- `/dev` : Device files.
- `/proc` : acts as an interface to internal data structures in the kernel and processes .
- `/usr` : "User System Resources" the location of user programs and file
  - `/usr/bin` : Contains ordinary commands and shell scripts
---


## Basic Concepts and Commands

### Commands in Linux

Linux commands are categorized into two types:

- **Internal Commands**: Built into the shell (e.g., `cd`, `echo`, `pwd`).
- **External Commands**: Executable files stored in system directories (e.g., `ls`, `mkdir`, `cp`).

To determine if a command is internal or external:

#### Commands:

- `type <command>` : Shows whether a command is built-in or an external binary.
- `which <command>` : Locates the path of an external command.

### Getting Help for Commands

To understand how a command works, use:

#### Commands:

- `help <builtin-command>` : Shows help for shell built-in commands.
- `<external-command> --help` : Displays usage information for external commands.
- `man <command>` : Opens the manual page for detailed documentation.


### Displaying File Contents

To view file contents, use:

#### Commands:

- `cat <file>` : Display entire file contents.
- `less <file>` : View file page by page (allows scrolling up/down).
- `more <file>` : Similar to `less`, but only allows scrolling forward.
- `nano <file>` : Open file in Nano text editor (simple interface).
- `vi <file>` : Open file in Vi editor (powerful but complex).


### Paths (Relative and Absolute)

- **Absolute Path**: The complete path starting from the root `/`.
- **Relative Path**: A path relative to the current directory.

#### Commands:

- `pwd` : Show the **absolute path of the current working directory**.
- `cd <directory>` : Change directory.
  - `cd ..` : Move to **previous directory**.
  - `cd .` : Stay in **current directory**.
  - `cd -` : Switch to **previous working directory**.
  - `cd ~` : Move to **home directory**.

### Listing Files and Directories

To explore the contents of a directory, use the following commands:

#### Commands:

- `ls -aR` : List all directories and files, including hidden items and subdirectories.
- `ls -al` : List all directories and files, including hidden items in long format.

### Creating, Copying, Moving, and Deleting Files

File management is a fundamental part of Linux operations.

#### Commands:

- `mkdir <dir>` : Create a directory.
  - `mkdir -p <dir>` : Create intermediate folders if needed.
- `cp <source> <destination>` : Copy files.
  - `cp -r <source> <destination>` : Recursively copy directories.
- `mv <source> <destination>` : Move or rename files.
- `rm -rf <file>` : Force delete a file or directory.
- `tree <dir>` : Show directory structure.
  - `tree -a` : Include hidden files.


--- 
## Clearing the Terminal

To clean up your workspace:
### Commands:

- `clear` : Clears the terminal screen.
- `Ctrl + L` : Alternative shortcut to clear the screen.

## History Command in Linux

The `history` command maintains a list of previously executed commands, allowing users to recall and reuse them efficiently.

### Basic Usage
- `history` : Display the list of recently used commands.
- `!n` : Execute the command numbered `n` in the history.
- `!!` : Execute the last command again.
- `!string` : Execute the most recent command that starts with `string`.
- `history -c` : Clear the command history.

### Searching Command History
- `Ctrl + R` : Start reverse search in history.
- `Ctrl + R` again : Cycle through matches.
- `Ctrl + G` : Exit reverse search.

---

## Wildcards in Linux

### Using Wildcards for Flexible File Operations

Wildcards allow pattern matching when working with multiple files and directories, making file operations more efficient and dynamic.

#### Common Wildcards:

- `*` : Matches **any number of characters** (including none).
  - Example: `ls *.txt` lists all `.txt` files in the directory.
- `?` : Matches **a single character**.
  - Example: `ls file?.txt` matches `file1.txt`, `file2.txt`, but not `file10.txt`.
- `[ ]` : Matches **any one of the characters inside the brackets**.
  - Example: `ls file[123].txt` matches `file1.txt`, `file2.txt`, or `file3.txt`.
- `[! ]` : Matches **any character NOT inside the brackets**.
  - Example: `ls file[!1].txt` matches `file2.txt`, `file3.txt`, but not `file1.txt`.
- `{ }` : Expands to **multiple possible values**.
  - Example: `ls {file1,file2}.txt` matches `file1.txt` and `file2.txt`.
- `~` : Expands to the **home directory of the current user**.
  - Example: `cd ~/Documents` moves to the `Documents` directory in the home folder.

### Escape Sequences

When working with files or directories that contain spaces or special characters, use escape sequences:

- `\` : Escape a special character.
  - Example: `ls My\ File.txt` allows access to `My File.txt`.
- Quotes (`""` or `''`) : Enclose filenames with spaces.
  - Example: `ls "My File.txt"` works similarly.

### Practical Usage

- `rm *.log` : Deletes all `.log` files.
- `cp report_2023?.pdf ~/backup/` : Copies `report_20230.pdf`, `report_20231.pdf`, etc., to the backup folder.
- `mv file{1,2,3}.txt ~/archive/` : Moves `file1.txt`, `file2.txt`, and `file3.txt` to the archive directory.

---
## Regular Expressions (Regex) in Linux

Regular expressions (Regex) are powerful tools for pattern matching and text processing in Linux. They are used in various command-line utilities such as `grep`, `sed`, `awk`, and `perl`.

### Basic Syntax

- `.` : Matches **any single character**.
  - Example: `c.t` matches `cat`, `cut`, `cot`.
- `*` : Matches **zero or more** occurrences of the preceding character.
  - Example: `go*` matches `g`, `go`, `goo`, `gooo`.
- `+` : Matches **one or more** occurrences of the preceding character.
  - Example: `go+` matches `go`, `goo`, `gooo` but not `g`.
- `?` : Matches **zero or one** occurrence of the preceding character.
  - Example: `colou?r` matches `color` and `colour`.
- `[]` : Matches **any single character** inside the brackets.
  - Example: `[abc]` matches `a`, `b`, or `c`.
- `[^ ]` : Matches **any character NOT inside** the brackets.
  - Example: `[^0-9]` matches any character except digits.
- `{n,m}` : Matches **n to m** occurrences of the preceding character.
  - Example: `a{2,4}` matches `aa`, `aaa`, or `aaaa`.
- `|` : Acts as an **OR operator**.
  - Example: `cat|dog` matches `cat` or `dog`.
- `^` : Matches the **beginning** of a line.
  - Example: `^Hello` matches lines starting with `Hello`.
- `$` : Matches the **end** of a line.
  - Example: `world$` matches lines ending with `world`.
- `\` : Escapes special characters.
  - Example: `\.` matches a literal `.`.

## Common Commands Using Regex

- `grep 'pattern' file` : Searches for lines matching `pattern` in `file`.
- `sed 's/old/new/g' file` : Replaces `old` with `new` in `file`.
- `awk '/pattern/ {print $0}' file` : Prints lines matching `pattern` in `file`.

---


## System Information & Utilities in Linux

Linux provides various commands to retrieve system information, including kernel details, hardware status, and process management.

### System Information Commands

- `uname -a` : Displays complete system information.
- `uname -r` : Shows the Linux kernel version.
- `hostname` : Prints the system's hostname.
- `uptime` : Displays how long the system has been running.
- `whoami` : Shows the current logged-in user.
- `df -h` : Displays disk usage in a human-readable format.
- `du -sh <directory>` : Shows the size of a directory.
- `free -h` : Displays available and used memory.
- `top` / `htop` : Monitors real-time system processes.



