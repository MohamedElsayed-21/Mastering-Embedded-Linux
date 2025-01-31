## Introduction to Shell Scripting in Linux

Shell scripts in Linux provide a powerful and efficient way to automate repetitive or complex tasks, making them essential tools for system administrators, developers, and power users. By using Bash (Bourne Again SHell), a widely adopted command-line interpreter, you can streamline workflows, manage systems, and automate operations.

---

## Command Types in Bash

### Built-in Commands

These commands are part of the shell itself and do not require external programs. Examples include:

- `cd`
- `echo`
- `exit`
- `history`

### External Commands

These commands are stored as executable files in directories such as `/bin`, `/usr/bin`, or `/sbin`. Examples include:

- `ls`
- `cp`
- `mv`
- `grep`
- `cat`

### Aliases

User-defined shortcuts for frequently used or complex commands. You can create an alias using the `alias` keyword:

```bash
alias ll='ls -l'
```

### Identifying Command Types

Use the `type` command to determine if a command is built-in, external, or an alias:

```bash
type cd
type ls
type ll
```

---

## Writing Your First Shell Script

### Creating the Script

1. Create a file named `first.sh`:
   ```bash
   vi first.sh
   ```
2. Add the following content to list files in a directory:
   ```bash
   cd /
   pwd
   cd 
   ls -al
   ```

### Running the Script

There are two primary ways to execute a shell script:

#### Using the `bash` Command

```bash
bash first.sh
```

#### Running as an Executable

1. Make the script executable:
   ```bash
   chmod u+x first.sh
   ```
2. Run the script directly:
   ```bash
   ./first.sh
   ```

**Note:** Avoid naming scripts with the `.sh` extension if you plan to use them as executables to prevent ambiguity.

---

## Configuring a Script as a Command

When a command is executed, the operating system searches for the script or executable in the directories listed in the `$PATH` environment variable. If it cannot find the command, it throws a `command not found` error.

### Adding Your Script to `$PATH`

1. Append the directory containing the script to the `$PATH` variable:
   ```bash
   export PATH=$PATH:/path/to/script/directory
   ```
2. Run the script as a command:
   ```bash
   first
   ```
3. Verify the command’s location:
   ```bash
   which first
   ```

---

## Basic Syntax and Structure

### Shebang (`#!`)

The shebang line specifies the interpreter that will execute the script. It must appear at the very top of the script.

```bash
#!/bin/bash
```

#### Common Interpreters

- `#!/bin/bash`: Bash shell.
- `#!/bin/sh`: Bourne shell (portable).
- `#!/usr/bin/env bash`: Portable shebang using `env`.

### Comments in bash

Comments are ignored during execution and are useful for documenting the script:

```bash
# This is a comment
echo "This is a simple Bash script"  # Inline comment
```

#### Multi-Line Comments

Use a `: <<'EOF'` block (Heredoc) for multi-line comments:

```bash
: <<'EOF'
This is a multi-line comment.
You can write as many lines as you want here.
EOF
```

---

## Best Practices for Writing Shell Scripts
- Give your script a name that makes sense .
- Leave out .sh extension for executable .
- Add comments to explain the purpose and logic of your script.

