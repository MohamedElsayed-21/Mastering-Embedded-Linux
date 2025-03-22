# Memory Layout of a Process

Each process is allocated memory in distinct segments:

### **Memory Segments**

- **Text Segment**: Contains the program’s machine code instructions. This section is **read-only and sharable**.
- **Initialized Data Segment**: Stores global and static variables **explicitly initialized** in the code.
- **Uninitialized Data Segment (BSS)**: Stores global/static variables **not explicitly initialized**, which are initialized to `0` at runtime.
- **Heap**: Used for dynamic memory allocation (`malloc()`, `free()`). The heap **grows upwards**.
- **Stack**: Used for function calls, local variables, and return addresses. The stack **grows downwards**.

### **Memory Layout in x86-32 Architecture**

- The **Stack and Heap are dynamic**.
- The **Kernel Space is mapped into process memory** but is inaccessible to the user.
- **Special Symbols**:
  - `etext`: End of the text segment.
  - `edata`: End of the initialized data segment.
  - `end`: End of the uninitialized data segment.

*Refer to the memory layout diagram for visual representation.*

---

## Virtual Memory Management

### **Concept of Virtual Memory**

Linux uses **virtual memory management** to efficiently use both CPU and RAM by leveraging **locality of reference**:

- **Spatial locality**: Accessing memory addresses near recently accessed locations.
- **Temporal locality**: Reusing recently accessed memory locations.

### **Virtual Memory Mechanism**

- **Memory is split into pages** (fixed-size blocks).
- **RAM is divided into page frames** (same size as pages).
- **Only active pages are kept in RAM**; unused pages are stored in **swap space**.
- When a process accesses a page that is not in RAM, a **page fault** occurs, prompting the kernel to load the page from disk.

### **Page Tables and Address Translation**

Each process has a **page table** that:

- Maps virtual pages to **physical memory locations**.
- Keeps track of whether a page is in RAM or swap.
- Prevents processes from accessing unauthorized memory.

If a process accesses a memory address **without a valid page-table entry**, a **segmentation fault (SIGSEGV)** occurs.

*Refer to the page table and virtual memory diagram for a clearer view.*

---

## Advantages of Virtual Memory Management

### **Process Isolation**

Each process operates in its own virtual address space, preventing it from accessing another process’s memory.

### **Memory Sharing**

- Processes can **share read-only code** (e.g., shared libraries).
- Explicit memory sharing can be done via **shmget()** and **mmap()**.

### **Memory Protection**

- Pages can be marked as **read-only, read-write, or executable**.
- Different processes can have **different permissions** on shared memory.

### **Simplifies Programming**

- Programmers don’t need to worry about physical memory allocation.
- Programs can use **more memory than physically available** due to paging.

---

## User Stack vs. Kernel Stack

- **User Stack**: Regular function call stack in user-space memory.
- **Kernel Stack**: Used exclusively for system calls and interrupt handling. Each process has a **separate kernel stack**.

### **User Stack Frame Components**:

- **Function Arguments and Local Variables**:
  - Automatic variables (created and destroyed with function calls).
- **Call Linkage Information**:
  - Stores CPU registers (including the program counter) so that execution resumes correctly after function returns.


