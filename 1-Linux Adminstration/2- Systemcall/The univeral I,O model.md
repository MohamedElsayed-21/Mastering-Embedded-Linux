# File I/O: The Universal I/O Model

File input and output (I/O) are at the heart of the UNIX system call API, as files are a fundamental part of the UNIX philosophy. The system relies on **file descriptors**, which are small, nonnegative integers used by a process to refer to open files. These descriptors apply to **all types of files**, including disk files, pipes, FIFOs, sockets, terminals, and device files.  

## File Descriptors and Standard I/O

Each process has its **own set of file descriptors**, which it typically **inherits** from the shell when the program starts. UNIX systems define three standard file descriptors that most programs rely on:  

| **Descriptor** | **File**        | **FD Number** |
|---------------|----------------|--------------|
| **stdin**     | Standard Input  | 0            |
| **stdout**    | Standard Output | 1            |
| **stderr**    | Standard Error  | 2            |

These descriptors allow programs to interact with input, output, and error streams in a structured way. In an interactive shell, they usually point to the **terminal**. However, when I/O redirection is used, the shell modifies these file descriptors before executing the program, enabling input and output to be redirected to **files or other processes**.  

###  Using File Descriptors in Programs  

When working with file descriptors in a program, they can be referenced in **two ways**:  
- By their numerical values (`0`, `1`, or `2`).  
- By using **POSIX standard names** defined in `<unistd.h>`, which provide clearer, more readable code.  

Beyond these low-level descriptors, UNIX also provides **higher-level file streams** such as `stdin`, `stdout`, and `stderr`. These streams initially correspond to the process’s standard input, output, and error, but they are **not fixed**—they can be **redirected to other files** using the `freopen()` function.  

### Redirecting Streams with `freopen()` 

The `freopen()` function allows a program to **redirect** standard I/O streams to a different file. For example, calling `freopen()` on `stdout` can direct all output to a specific file instead of the terminal. However, it’s important to note that **this may change the underlying file descriptor**. If `stdout` was originally linked to file descriptor `1`, it might get assigned a different descriptor after redirection, meaning it’s no longer safe to assume that `stdout` still corresponds to FD `1`.  

This ability to manipulate file descriptors and streams gives UNIX its **flexibility** in handling I/O operations, allowing processes to work with different types of data sources in a seamless and efficient manner.

##  **Why "Everything in Linux is a File"?**

In Linux, the concept "everything is a file" comes from the fact that almost all resources are accessed using the same basic system calls: `open()`, `read()`, `write()`, and `close()`.  

The kernel abstracts devices, sockets, pipes, and regular files under a unified file interface using file descriptors.  
This design simplifies resource management, ensures consistency, and promotes portability.

Performing file input and output (I/O) in UNIX is built around four essential **system calls**. While most programming languages and software packages interact with these calls indirectly through **I/O libraries**, understanding their functionality is crucial for low-level file operations.  

### **1. Opening a File – `open()`**  
The `open()` system call is used to open a file and obtain a **file descriptor**, which is then used for subsequent file operations.  

```c
fd = open(pathname, flags, mode);
```

- `pathname`: The path to the file.  
- `flags`: A **bitmask** that determines how the file is opened (e.g., read, write, append).  
- `mode`: The **permissions** to set if a new file is created (ignored if the file already exists).  

If the file does **not exist**, `open()` can create it based on the provided flags. On success, `open()` returns a file descriptor; otherwise, it returns `-1` to indicate an error.  

### **2. Reading from a File – `read()`**  
The `read()` system call reads data from an open file into a buffer.  

```c
numread = read(fd, buffer, count);
```

- `fd`: The file descriptor of the open file.  
- `buffer`: The memory location where data will be stored.  
- `count`: The maximum number of bytes to read.  

It returns the **number of bytes actually read**, which may be less than `count`. If the end of the file is reached, `read()` returns **0**.  

### **3. Writing to a File – `write()`**  
The `write()` system call writes data from a buffer to an open file.  

```c
numwritten = write(fd, buffer, count);
```

- `fd`: The file descriptor of the open file.  
- `buffer`: The data to be written.  
- `count`: The number of bytes to write.  

The return value is the **number of bytes actually written**, which might be less than `count` if, for example, the disk is full.  

### **4. Closing a File – `close()`**  
After completing all file operations, the `close()` system call releases the file descriptor and associated kernel resources.  

```c
status = close(fd);
```

- `fd`: The file descriptor to close.  

Closing a file ensures that any **pending writes** are flushed to disk and that system resources are freed. If a process terminates without closing its files, the **kernel automatically closes them**.  


**These system calls form the foundation of UNIX file I/O, allowing efficient and flexible handling of files at the system level.**

---

## **Creating a New File with `open()`**  

When `open()` is used to create a new file, the `mode` argument specifies the **permissions** that should be set on the file. The `mode_t` data type, which defines file permissions, is typically an **integer** (often specified in octal).  

However, the final permissions assigned to a new file depend not only on the `mode` argument but also on:  
1. **The process umask** – a value that restricts default permissions.  
2. **The default access control list (ACL)** of the parent directory (if applicable).  

Permissions can be defined either:  
- **Numerically** (e.g., `0644` for read-write permissions for the owner and read-only for others).  
- **Symbolically**, by **ORing (`|`)** bitmask constants together (e.g., `S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH`).  

Understanding these concepts allows efficient and secure file handling within UNIX systems, ensuring proper access control and data integrity.
**Understanding `open()` Flags in Linux**

The `open()` system call in Linux is used to open files and returns a file descriptor, which is an integer representing the opened file. The `flags` argument in `open()` determines how the file should be opened. The available flags are categorized as follows:

### **1. File Access Mode Flags**
These flags define how the file is accessed:
- `O_RDONLY` - Open for reading only.
- `O_WRONLY` - Open for writing only.
- `O_RDWR` - Open for both reading and writing.

### **2. File Creation Flags**
These flags affect the behavior of file creation and I/O operations:
- `O_CREAT` - Create the file if it does not exist.
- `O_EXCL` - Used with `O_CREAT` to ensure that the file is created exclusively (fails if the file already exists).
- `O_TRUNC` - If the file exists and is a regular file, it is truncated to zero length.
- `O_DIRECTORY` - Ensures that the given path is a directory; otherwise, `open()` fails.
- `O_NOFOLLOW` - Prevents `open()` from following symbolic links.
- `O_LARGEFILE` - Allows handling large files (>2GB) on 32-bit systems.
- `O_NOATIME` - Prevents updating the file's last access time when it is read.
- `O_CLOEXEC` - Ensures the file descriptor is closed during an `exec()` call.

### **3. Open File Status Flags**
These flags affect how the file behaves after being opened:
- `O_APPEND` - All writes are appended to the end of the file.
- `O_ASYNC` - Enables asynchronous I/O notifications.
- `O_DSYNC` - Ensures that writes are flushed to disk immediately for data integrity.
- `O_SYNC` - Ensures that both file data and metadata are flushed to disk.
- `O_NONBLOCK` - Opens the file in non-blocking mode.
- `O_NOCTTY` - Prevents the file from becoming the controlling terminal of the process.

Historically, early UNIX implementations used the numbers `0`, `1`, and `2` for **read-only, write-only, and read-write modes**, respectively. Modern UNIX systems define `O_RDONLY`, `O_WRONLY`, and `O_RDWR` to have these values. However, it's important to note that `O_RDWR` is **not equivalent** to `O_RDONLY | O_WRONLY`; combining these two flags would be a **logical error**.  

---


## **Reading from a File: `read()`**
The `read()` system call reads data from the open file referred to by the descriptor `fd`.

According to `man 2 read`:
- The `count` argument specifies the maximum number of bytes to read. (`size_t` is an unsigned integer type.)
- The `buffer` argument supplies the address of the memory buffer where the input data will be placed. This buffer must be at least `count` bytes long.
- System calls don’t allocate memory for buffers; instead, the caller must provide a pointer to a pre-allocated buffer of the correct size.

A successful call to `read()` returns:
- The number of bytes actually read.
- `0` if end-of-file (EOF) is encountered.
- `-1` if an error occurs (with `errno` set accordingly).

A `read()` call may read fewer bytes than requested, particularly when:
- Reading from a regular file near its end.
- Reading from pipes, FIFOs, sockets, or terminals, where various conditions can limit the number of bytes read. For example, a `read()` from a terminal typically stops at a newline (`\n`).

#### **Handling Null Termination in `read()`**
Unlike functions like `printf()`, `read()` does not automatically null-terminate strings. This is because `read()` is used for both text and binary data, and it cannot assume that the input consists of null-terminated strings.

If null termination is required, the caller must explicitly append a `\0` at the end of the buffer. As a result, the buffer must be allocated with at least one extra byte to store the null terminator if needed.

By understanding how `read()` works, developers can handle file input efficiently and avoid common pitfalls related to buffer allocation and string handling.

---

## **Writing to a File: `write()`**
The arguments to `write()` are similar to those for `read()`:
- `buffer` is the address of the data to be written.
- `count` is the number of bytes to write from `buffer`.
- `fd` is a file descriptor referring to the file to which data is to be written.

On success, `write()` returns the number of bytes actually written; this may be less than `count`. Possible reasons for a partial write include:
- The disk being full.
- The process resource limit on file sizes being reached (`RLIMIT_FSIZE`).

When performing I/O on a disk file, a successful return from `write()` does not guarantee that the data has been physically written to disk. This is because the kernel buffers disk I/O to optimize performance. Details on how to ensure data persistence are covered in Chapter 13.

---

## **Closing a File: `close()`**
The `close()` system call closes an open file descriptor, freeing it for subsequent reuse by the process. When a process terminates, all of its open file descriptors are automatically closed.

It is good practice to explicitly close unneeded file descriptors to:
- Improve code readability and maintainability.
- Prevent running out of file descriptors, which can be a critical issue for long-lived processes such as servers.

Errors that can occur when calling `close()` include:
- Attempting to close an unopened file descriptor.
- Closing the same file descriptor multiple times.
- Specific file system-related errors during the close operation.

By properly managing file descriptors with `close()`, developers can create robust applications that handle resources efficiently.
