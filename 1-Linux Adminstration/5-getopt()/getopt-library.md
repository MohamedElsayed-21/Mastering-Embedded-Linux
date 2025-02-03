# Documentation: Hashing in C with Bash Interaction

## Overview

This C program computes SHA-1 and SHA-256 hashes for a given input string using OpenSSL's EVP API. It interacts with the shell (Bash) by processing command-line arguments using `getopt()`, a standard Unix function for parsing options. The program allows users to specify which hash function to use via command-line options.


 ## What is `getopt()` and its Alternatives?
- `getopt()` is a function in the C standard library used to parse command-line arguments.
- It simplifies argument handling by processing options and their associated values in a structured way.
- Alternatives to `getopt()` include:
  - **`getopt_long()`**: Supports long-form options (e.g., `--hash` instead of `-a`).
  - **`argp_parse()`**: A more advanced parser that provides structured argument parsing.
  - **Manual Parsing**: Using `argc` and `argv` directly for custom argument handling.



## How the Bash Interaction Works

1. **Command-Line Arguments:** The program takes input from the command line and processes options using `getopt()`. The format is:
   ```sh
   ./hash_program -a "text"  # Compute SHA-256
   ./hash_program -b "text"  # Compute SHA-1
   ```
2. **Option Parsing with `getopt()`**:
   - The program expects either `-a` for SHA-256 or `-b` for SHA-1.
   - `optind` is used to track the argument index in `argv`.
   - The input text is stored and passed to the appropriate hash function.

## Code Breakdown

### 1. **Main Function**

- It determines whether to compute SHA-256 or SHA-1 based on options.
    `-a` for  Computing SHA-256
    `-b` for Computing  SHA-1
- The program takes user input via command-line arguments.
- The `getopt()` function processes the arguments.
- The OpenSSL EVP API is used for secure hash computation.
- The program is designed to be easily used within Bash scripts or manually from the terminal.


--- 

```c
int main(int argc, char *argv[]) {
    int opt;
    char *input = NULL;

    if (argc < 3) {
        printf("Usage: %s -a <text> or -b <text>\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "a:b:")) != -1) {
        switch (opt) {
            case 'a':
                input = argv[optind - 1];
                if (input != NULL) {
                    calculate_sha256(input);
                }
                break;
            case 'b':
                input = argv[optind - 1];
                if (input != NULL) {
                    calculate_sha1(input);
                }
                break;
            case '?':
                printf("Unknown option\n");
                break;
        }
    }

    return 0;
}
```

- Parses command-line options `-a` and `-b`.
- Calls the appropriate hash function based on user input.

### 2. **SHA-256 Calculation**

```c
void calculate_sha256(const char *input) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    
    if (ctx == NULL) {
        printf("Error initializing EVP_MD_CTX\n");
        return;
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(ctx, input, strlen(input)) != 1 ||
        EVP_DigestFinal_ex(ctx, hash, &length) != 1) {
        printf("Error computing SHA-256\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    printf("SHA-256: ");
    for (unsigned int i = 0; i < length; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    EVP_MD_CTX_free(ctx);
}
```

- Uses OpenSSL to compute SHA-256.
- Handles initialization, updating, and finalization of the hash computation.
- Prints the hash in hexadecimal format.

### 3. **SHA-1 Calculation**

Works similarly to SHA-256 but uses `EVP_sha1()` instead of `EVP_sha256()`.

## Example Usage in Bash

```sh
$ ./hash_program -a "hello"
SHA-256: 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824

$ ./hash_program -b "hello"
SHA-1: 5d41402abc4b2a76b9719d911017c592
```


