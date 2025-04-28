# Understanding System Calls in Linux

## **Introduction to System Calls**

**System calls** serve as an **interface** between user applications and the operating system kernel.
A **system call** is a controlled entry point into the **kernel**, allowing user-space programs to request system-level services, such as:

- Process creation
- File and I/O operations
- Memory management
- Interprocess communication

## **How to invoke a system call**
There are two ways to invoke a system call:
### 1. **Direct System Call:**
   - The program directly places arguments into CPU registers and invokes the system call using an assembly instruction (e.g., `syscall` or `int 0x80`).
   - Bypasses `glibc` and interacts directly with the kernel.
   - Requires knowledge of system call numbers and CPU-specific calling conventions.
### 2. **Using a Wrapper Function:**
- A **library function** is a function provided by the **C standard library (glibc)**. Some are **independent** (e.g., string manipulation functions), while others act as **wrappers** around system calls. The function names in `glibc` remain **constant**, but their implementations may change based on the underlying system call being executed. Additionally, system call names can vary depending on the **architecture** and system specifications.
   - A `glibc` function calls the system call indirectly, handling argument placement and error handling.
   - Provides a consistent interface across different architectures.
   - Example: `write()` in `glibc` calls the `sys_write` system call internally.


#### **System Calls vs Function Calls:**
  - System calls (`write`, `read`) involve **kernel interaction**.
  - Function calls (`printf`, `strcmp`) are handled in **user space** unless they internally call system calls.

#### **GNU C Library (glibc) and Alternatives**
- **glibc** is the most widely used C library on Linux.
- **Alternative lightweight C libraries**:
  - `uClibc` (for embedded systems)
  - `diet libc` (optimized for small binaries)



## How a System Call is Invoked (Through glibc)

### Step-by-Step:

1. **Application Calls a Wrapper Function:**
   - A function in the **C standard library (glibc)** is used to simplify system call invocation.
      - Example: `fopen()` from glibc internally calls Linux’s `open()` system call.
   - **Argument Handling**: The wrapper copies function arguments to the appropriate CPU **registers**.

2. **Calling into linux-gate.so (VDSO):**
   - `linux-gate.so` is a **Virtual Dynamic Shared Object** mapped into every process's address space.
   - It contains optimized machine code to initiate system calls.
   - Each system call has a unique **number**, stored in register **%eax**  You can view the system call table in `/usr/include/x86_64-linux-gnu/asm/unistd_64.h`.
   
3. **Triggering the System Call:**
   - glibc calls `__kernel_vsyscall` function.
   - This triggers the `int 0x80` or `sysenter` instruction on newer x86 architecture:
     - CPU switches to **privileged mode**.
     - Stack Pointer (SP) and Instruction Pointer (IP) are updated.
     - Segment registers are adjusted for kernel execution.

4. **Kernel Side Execution:**
   - Control transfers to the **SYSENTER entry point** in the kernel.
   - The kernel:
     - Looks up the **system call number** in the **dispatch table**.
     - Calls the appropriate **system call handler** from `sys_call_table`.
     - Checks and processes arguments.
5. **Execution of the System Call Handler:**
   - The handler may take time if it involves I/O or hardware access.
   - The OS might **context switch** the CPU to another process if needed.

6. **Returning to User Space:**
   - The handler places the **return value** into a CPU register.
   - The **SYSEXIT** instruction is executed:
     - Returns the CPU to **unprivileged mode**.
     - Restores user-space SP and IP.
     - Adjusts segment registers.

7. **glibc Continues Execution:**
   - It may perform post-processing.
   - If an error occurs, `errno` is set, and the wrapper returns an error code. 
      - Most system calls **return ****`-1`**** on failure** and set `errno`.
      - The `<errno.h>` header provides **error codes** (e.g., `EACCES`, `ENOMEM`).
      - Always check **the function's return value first**, then `errno`.
   - Eventually returns control back to the user's program.

**This picture illustrating How System Calls Work**

![Steps in the execution of a system call](../Images/Steps%20in%20the%20execution%20of%20a%20system%20call.png)


## Direct System Calls (Without glibc)
- Programs can **directly invoke system calls** without relying on `glibc`.
- However, this method **reduces portability** across different UNIX systems, since the details are often **architecture-specific**.

## How Direct System Calls Work:

- Direct system calls require **using assembly instructions** specific to the CPU architecture.
- Refer to `man 2 syscall` for information about syscall usage in different architectures.

- **Important:**  
  CPU **registers** (not the stack) are used to pass arguments between **user space** and **kernel space**, because the user stack and kernel stack are **separate** and **cannot** be directly shared.


### Steps to Make a Direct System Call:

1. Identify the CPU Architecture:
- Use the command:  
  ```bash
  uname -p
  ```

2. Pass Arguments Through Registers:
- According to `man syscall`, for **x86-64 architecture**, arguments are passed via registers in this order:
```
 Arch/ABI      arg1  arg2  arg3  arg4  arg5  arg6  arg7  Notes
  x86-64        rdi   rsi   rdx   r10   r8    r9    -
```

- **Note:**  
  If a system call requires **more than six arguments**, memory must be used to pass additional parameters (e.g., passing a pointer to a structure).

> Think of it as using a **memory API** to send complex or large data.

3. Define the System Call Number:

- The **system call number** is placed into the `rax` register.
- To find system call numbers:
  - Check header file:  
    ```bash
    /usr/include/x86_64-linux-gnu/asm/unistd_64.h
    ```
  - Or directly view the Linux kernel syscall table:  
    ```bash
    linux/arch/x86/entry/syscalls/syscall_64.tbl
    ```

Example from syscall table:

```
 Arch/ABI    Instruction           System  Ret  Ret  Error    Notes
                                         call #  val  val2
       ───────────────────────────────────────────────────────────────────

x86-64      syscall               rax     rax  rdx  -        5
```

4. Assemble and Link Your Program:

- Install the assembler:
  ```bash
  sudo apt install nasm
  ```
- This is the assembly instration for intel x86 64bit
   ```asmbley
   global main            ; Entry point for the linker

   SECTION .data
      msg: db "Hello World from x86_64 machine", 0Ah, 0h  ; Message + newline + null terminator
      len_msg: equ $ - msg                                ; Calculate length of the message

   SECTION .text
   main:
      ; syscall: write(int fd, const void *buf, size_t count)
      mov rax, 1          ; Syscall number for write = 1
      mov rdi, 1          ; File descriptor 1 = stdout
      mov rsi, msg        ; Pointer to the message
      mov rdx, len_msg    ; Length of the message
      syscall             ; Make the syscall

      ; Save the return value (number of bytes written) into r15
      mov r15, rax

      ; syscall: exit(int status)
      mov rax, 60         ; Syscall number for exit = 60
      mov rdi, r15        ; Use the number of bytes written as the exit code
      syscall             ; Make the syscall
   ```
   
- Compile the assembly code:
  ```bash
  nasm -f elf64 syscall64.nasm
  ```

- Link the object file:
  ```bash
  ld syscall64.o --entry main -o my64syscall
  ```



## Benefits of glibc Wrapper Functions:

| Benefit                  | Explanation                                                                 |
|---------------------------|-----------------------------------------------------------------------------|
| **Modularity**            | Clean separation between user and kernel interactions.                    |
| **Portability**           | Code can run across multiple UNIX-like systems with minimal changes.       |
| **Source Compatibility**  | No need to manually manage system-specific details.                        |
| **Architecture Abstraction** | Hides complex, architecture-specific instructions like SYSENTER or SYSCALL. |
