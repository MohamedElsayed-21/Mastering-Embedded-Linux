# Handling Input in Bash

Bash provides multiple ways to handle input, including command-line arguments, interactive input, and reading from files. This document explores these methods with examples.

## 1. Command-Line Arguments

Bash scripts can receive arguments passed from the command line. These arguments are accessible using special variables:

- `$0` : The script name
- `$1, $2, ...` : Positional parameters
- `$#` : Number of arguments
- `$@` : All arguments as separate words
- `$*` : All arguments as a single string
- `$?` : Exit status of the last executed command
- `$$` : Process ID of the script
- `$!` : Process ID of the last background command

### Example:

```bash
#!/bin/bash
echo "Script name: $0"
echo "First argument: $1"
echo "All arguments: $@"
echo "Number of arguments: $#"
```



Run with:

```sh
bash script.sh arg1 arg2 arg3
```

## 2. Interactive Input (Reading from User)

The `read` command allows reading user input interactively and supports multiple options such as `-p` for prompts, `-s` for silent input (e.g., passwords), `-t` for timeouts, and `-n` for reading a specific number of characters.

### Example:

```bash
#!/bin/bash
echo "Enter your name:"
read name
echo "Hello, $name!"
```

- `read -p "Prompt text" var` : Read with a prompt and store the input in var
- `read -s var` : Silent mode (e.g., passwords)
- `read -t 5 var` : Timeout after 5 seconds
- `read -n 1 var` : Read only one character
- `read -d delimiter var` : Read until a specific delimiter
- `read -a array_var` : Read input into an array
- `read -r var` : Prevent backslashes from being interpreted as escape characters

### Example with options:

```bash
#!/bin/bash
read -p "Enter username: " username
read -s -p "Enter password: " password
read -a hobbies -p "Enter your hobbies (space-separated): "
echo -e "\nWelcome, $username!"
echo "Your hobbies: ${hobbies[*]}"
```

## 3. Reading Input from a File

Bash scripts can read input from files using `while read` loops .

### Example using `while read`:

```bash
#!/bin/bash
while read line; do
    echo "Read line: $line"
done < input.txt
```

## 4. Handling Input Using Flags

Bash scripts can also process input using flags (options) provided in the command line. The `getopts` command is commonly used for parsing options.

### Example using `getopts`:

```bash
#!/bin/bash
while getopts "u:p:h" opt; do
  case $opt in
    u) user=$OPTARG ;;
    p) pass=$OPTARG ;;
    h) echo "Usage: script.sh -u username -p password"; exit 0 ;;
    *) echo "Invalid option"; exit 1 ;;
  esac
done

echo "User: $user, Password: $pass"
```

Run with:

```sh
bash script.sh -u myuser -p mypassword
```

The `getopts` command processes options and their arguments, allowing for more structured and user-friendly scripts.



