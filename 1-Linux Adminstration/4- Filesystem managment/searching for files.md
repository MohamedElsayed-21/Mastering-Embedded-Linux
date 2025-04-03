# Searching for Files in Linux

Searching for files efficiently is an essential skill in Linux. There are multiple commands available depending on the complexity and specificity of the search.

## 1. Searching for Binary Files

To locate the absolute path of a binary (executable) file, use:

```bash
which <command>
```

Example:

```bash
which ls
```

This returns the full path of the `ls` binary.

## 2. Simple Search Using `locate`

The `locate` command is a fast way to search for files by name. It uses a pre-built database of file locations rather than scanning the filesystem in real-time.

```bash
locate <filename>
locate <part-of-the-path>
```

Before using `locate`, ensure the database is updated:

```bash
sudo updatedb
```

### Limitations of `locate`

- Relies on a database (`/var/lib/mlocate/mlocate.db`), which may not reflect recent file changes.
- Does not perform deep filtering based on attributes like size, modification time, or file type.

## 3. Smarter Search Using `find`

The `find` command is more powerful than `locate`, allowing you to search files based on various criteria like name, size, type, permissions, owner, and modification time. It also allows skipping directories and performing actions on found files.

### Basic Syntax:

```bash
find <scope> <filter> <action>
```

### 3.1 Filtering by Type

```bash
find <scope> -type <type>
```

#### File Types:

- `d` – Directory
- `f` – Regular file
- `l` – Symbolic link
- `c` – Character device
- `b` – Block device

Example:

```bash
find /home -type d   # Find all directories in /home
```

### 3.2 Filtering by Name

```bash
find <scope> -name "<filename or pattern>"
```

Case-insensitive search:

```bash
find <scope> -iname "<filename or pattern>"
```

Example:

```bash
find ~ -name "*.xml"
find ~ -name \*\.xml
```

### 3.3 Filtering by Size

```bash
find <scope> -size <size>
```

- `+` means **larger than**
- `-` means **smaller than**
- No sign means **exact size**
- Units:
  - `M` → Megabytes
  - `G` → Gigabytes
  - `k` → Kilobytes
  - `c` → Characters (1 byte each)
  - `b` → Blocks (512 bytes, default if no unit is provided)

Example:

```bash
find ~ -size +1M  # Find all files larger than 1MB
```

### 3.4 Filtering by Permissions

```bash
find <scope> -perm <permissions>
```

Example:

```bash
find ~ -perm 777  # Find all files with full read, write, and execute permissions
```

### 3.5 Filtering by User

```bash
find <scope> -user <username>
```

Example:

```bash
find . -user root  # Find all files owned by root
```

### 3.6 Filtering by Modification Time

```bash
find <scope> -mtime <days>
```

Example:

```bash
find ~ -mtime -50  # Find all files modified in the last 50 days
```

## 4. Combining Filters

Filters can be combined using **AND**, **OR**, and **NOT** operators.

- **AND (`-a`, `-and`, or simply place filters back to back)**

```bash
find <scope> -size +1M -type f
```

- **OR (`-o` or `-or`)**

```bash
find <scope> -name "file1.txt" -o -name "file2.txt"
```

- **NOT (`!` or `-not`)**

```bash
find <scope> ! -name "*.log"
```

- **Using Parentheses (escaped with `\`):**

```bash
find . \( -name "*.c" -o -name "*.h" \)
```

## 5. Skipping Directories (`-prune`)

To exclude certain directories from the search, use `-prune`:

```bash
find . -type d \( -path ./dir1 -o -path ./dir2 \) -prune -o -print
```

This excludes `dir1` and `dir2` from the search.

## 6. Executing Actions on Found Files

The `-exec` and `-ok` options allow performing actions on found files.

- **`-exec`** executes the command without confirmation:

```bash
find ~ -name "*.pdf" -exec rm {} \;
```

- **`-ok`** asks for confirmation before executing:

```bash
find ~ -name "*.pdf" -ok rm {} \;
```

- **Faster execution using `+` instead of `;` to batch process files:**

```bash
find ~ -name "*.java" -exec cp {} {}.old +
```

## 7. Searching with Regular Expressions

Use `-regex` for regex-based searches:

```bash
find <scope> -regex "<pattern>"
```

Example:

```bash
find . -regex ".*/[a-z]+\.txt"
```

## Summary

| Command                               | Use Case                                |
| ------------------------------------- | --------------------------------------- |
| `which <cmd>`                         | Find binary location                    |
| `locate <filename>`                   | Fast search using prebuilt database     |
| `find <scope> -name <pattern>`        | Search files by name                    |
| `find <scope> -size +10M`             | Find files larger than 10MB             |
| `find <scope> -perm 777`              | Find files with specific permissions    |
| `find <scope> -user <username>`       | Find files owned by a user              |
| `find <scope> -mtime -10`             | Find files modified in the last 10 days |
| `find <scope> -type f -exec rm {} \;` | Delete found files                      |
| `find <scope> -type d -prune`         | Exclude directories from search         |




### **Problem Description**  
We need to test `find` commands for deleting files based on their extensions or excluding specific files from deletion.  

#### **Requirements:**  
1. **Create a test directory** with:  
   - `.bak` files  
   - `.log` files  
   - A `temp_003.tmp` file  
   - A regular file (e.g., `file_to_delete.txt`)  

2. **Apply the following `find` commands:**  
   - Delete `.bak` and `.log` files with confirmation.  
   - Delete all files except `temp_003.tmp` and the current directory (`.`).

### **Solution**  
- for creating files 
    ```
    touch file{1..3}.{bak,log} temp_003.tmp
    ```
- for deleting files
  - **First method:**  
    ```bash
    find . \( -name "*.bak" -or -name "*.log" \) -ok rm {} \;
    ```
    - Searches for all files with the `.bak` or `.log` extensions in the current directory (`.`) and its subdirectories.  
    - Uses `-ok rm {}` to delete the files, but prompts the user for confirmation before removing each file.  

  - **Second method:**  
    ```bash
    find . -not -name "temp_003.tmp" -not -name "." -exec rm {} \;
    ```
    - Deletes all files and directories in the current directory (`.`) **except** for `temp_003.tmp` and the directory itself (`.`).  
    - Uses `-exec rm {}` to remove the files **without** asking for confirmation.