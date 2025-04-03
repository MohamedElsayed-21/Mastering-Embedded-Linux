# Understanding System Calls in Linux

## **Introduction to System Calls**

**System calls** serve as an **interface** between user applications and the operating system kernel.
A **system call** is a controlled entry point into the **kernel**, allowing user-space programs to request system-level services, such as:

- Process creation
- File and I/O operations
- Memory management
- Interprocess communication


## **How System Calls Work**

Executing a system call follows a series of steps:

1. **Application Calls a Wrapper Function**: A function in the **C standard library (glibc)** is used to simplify system call invocation.
2. **Argument Handling**: The wrapper copies function arguments to the appropriate CPU **registers**.
3. **System Call Number Identification**: Each system call has a unique **number**, stored in register **%eax**  You can view the system call table in `/usr/include/x86_64-linux-gnu/asm/unistd_64.h`.
4. **Transition to Kernel Mode**: The wrapper executes a **trap instruction** (`int 0x80` or `sysenter` on newer CPUs) to switch to **kernel mode**.
5. **Kernel Processing**:
   - Saves register values.
   - Validates the system call number.
   - Retrieves the correct function from `sys_call_table`.
   - Checks and processes arguments.
   - Executes the system call.
6. **Return to User Mode**:
   - Restores register values.
   - Places return value on the stack.
   - Switches back to **user mode**.
7. **Error Handling **(`errno`)**: If an error occurs, `errno` is set, and the wrapper returns an error code.


**This picture illustrating How System Calls Work**

![Steps in the execution of a system call](../Images/Steps%20in%20the%20execution%20of%20a%20system%20call.png)


--- 

## **How to invoke a system call**
There are two ways to invoke a system call:
### 1. **Direct System Call:**
   - The program directly places arguments into CPU registers and invokes the system call using an assembly instruction (e.g., `syscall` or `int 0x80`).
   - Bypasses `glibc` and interacts directly with the kernel.
   - Requires knowledge of system call numbers and CPU-specific calling conventions.
### 2. **Using a Wrapper Function:**
A **library function** is a function provided by the **C standard library (glibc)**. Some are **independent** (e.g., string manipulation functions), while others act as **wrappers** around system calls. The function names in `glibc` remain **constant**, but their implementations may change based on the underlying system call being executed. Additionally, system call names can vary depending on the **architecture** and system specifications.
   - A `glibc` function calls the system call indirectly, handling argument placement and error handling.
   - Provides a consistent interface across different architectures.
   - Example: `write()` in `glibc` calls the `sys_write` system call internally.

#### **Examples of Wrapper Functions:**
  - `fopen()` → Calls `open()` system call.
  - `printf()` → Calls `write()` system call but adds formatting and buffering.
  - `malloc()` / `free()` → Manage memory allocation instead of using `brk()`. 


#### **GNU C Library (glibc) and Alternatives**
- **glibc** is the most widely used C library on Linux.
- **Alternative lightweight C libraries**:
  - `uClibc` (for embedded systems)
  - `diet libc` (optimized for small binaries)

## **Handling Errors in System Calls and Library Functions**

### **Checking System Call Return Values**
- Most system calls **return ****`-1`**** on failure** and set `errno`.
- The `<errno.h>` header provides **error codes** (e.g., `EACCES`, `ENOMEM`).
- Always check **the function's return value first**, then `errno`.
