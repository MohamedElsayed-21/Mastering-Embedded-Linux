# Linux Architecture Documentation

## Introduction

Linux, like all modern operating systems, follows a layered architecture to manage hardware resources efficiently and provide a stable environment for user applications. Understanding its structure helps in grasping concepts like system calls, privilege levels, and kernel functionalities.

---
## What is an Operating System (OS)?

The OS is **software** that:
- **Directly interacts with hardware**  
  - Only the OS is trusted to access hardware; user programs are not.
  - OS must be ported to new hardware; user programs remain portable.
- **Manages hardware resources**  
  - Allocates, schedules, and protects access to files, memory, display pixels, etc.
- **Provides high-level abstractions**  
  - Hides messy hardware details behind convenient, portable interfaces.


## Role of the Operating System
The operating system (OS) serves as an intermediary between user applications and the hardware. This ensures:
- **Process isolation [Abstraction]:**  
  - Processes are isolated but can share resources via controlled namespaces.
- **Self-protection [Security]:**  
  - Prevents user processes from directly accessing hardware.
- **Privileged access [Resource Management]:**  
  - User processes run in **unprivileged mode**.
  - OS runs in **privileged mode**.
  - User programs must use **system calls** to safely request OS services.

## Overview of Linux/GNU Architecture

Linux is structured into three primary layers:

1. **Hardware Layer**: The physical components, including the CPU, memory, storage, and peripheral devices.
2. **Kernel Space**: The core of the OS, responsible for managing system resources and providing controlled access to hardware. It includes essential components such as device drivers and system services.
3. **User Space**: Where user applications and system utilities execute, interacting with the kernel through system calls.
![Gnu-Linux Architecture](../Images/GNULinux%20arch%20.png)

## Privileged vs. User Mode

### The Mode Bit Mechanism

A **single mode bit** in the CPU’s control register determines the execution mode:

- `0` → **Kernel Mode** (full access to hardware and memory).
- `1` → **User Mode** ( Applications run with restricted privileges, unable to directly interact with hardware).

When a program in user mode requires hardware interaction, it must request services from the kernel via **system calls**.


## OS as an Abstraction Provider [System Calls]

The OS acts as the **layer below** user programs, providing services via **system calls** (APIs like POSIX, Windows, etc.).

**System Calls**: Bridging User Space and Kernel Space. System calls provide a controlled way for user applications to access OS services, such as:

Examples:
- **File System Access:** `open()`, `read()`, `write()`, `close()`
- **Network Stack Access:** `connect()`, `listen()`, `read()`, `write()`
- **Virtual Memory Management:** `brk()`, `shm_open()`
- **Process Management:** `fork()`, `wait()`, `nice()`


### What Happens When a Process Invokes a System Call?

1. **System Call Invocation:**
   - A user-space process (e.g., Process A) calls a system call.
   - The hardware switches the CPU to **privileged mode** and **traps** into the OS.
   - The OS invokes the appropriate **system call handler**.

2. **Execution in the OS:**
   - In privileged mode, the OS can execute privileged instructions and directly interact with hardware (e.g., disks).
   - Handling a system call might involve **long hardware interactions**.

3. **Returning to User Space:**
   - Once the system call is serviced:
     1. The CPU is switched back to **unprivileged mode**.
     2. Control returns to the **user-level code** in Process A.
   - The process continues running the next instruction after the system call.


### How Function Calls Are Handled

- **Pure glibc functions:**  
  - Some functions (e.g., `strcmp()` from `stdio.h`) are fully handled within glibc **without entering the kernel**.

- **glibc functions that call the kernel:**  
  - Some glibc routines internally invoke Linux system calls to access kernel services.

- **Direct system call invocation:**  
  - Programs can **directly invoke Linux system calls** without using glibc.
  - However, direct use of system calls can **reduce portability** across different UNIX-like systems.

### **What If the Program** Never Makes a System Call?

If a user-space program runs indefinitely without making system calls (e.g., an infinite loop), the OS relies on a **hardware timer**:

1. A **timer interrupt** is set when the program starts execution.
2. If the program does not yield control, the timer triggers an **interrupt**.
3. The CPU switches to **kernel mode**, and the OS schedules another process or resets the time slice.
4. Execution resumes in **user mode**.

To maintain control over running programs, the OS uses a **hardware timer** that ensures no single process monopolizes the CPU indefinitely. Preemptive scheduling ensures fair CPU allocation and system responsiveness.

## Kernel space
Linux is designed to support multiple hardware architectures, so it separates its code into architecture-dependent and architecture-independent components within the **kernel space**.

### **1. Architecture-Independent Components**
- These parts of the kernel work across different CPU architectures.
- Located in directories such as `kernel/`, `fs/`, `mm/`, and `net/` in the Linux source tree.

#### Kernel Subsystems

The Linux kernel is composed of multiple subsystems, each responsible for managing different aspects of the OS.

 - **Process Management**
    - Handles process creation, execution, and termination.
    - Implements scheduling policies to allocate CPU time fairly.
    - Uses system calls like `fork()`, `exec()`, and `wait()`.

  - **Memory Management**
    - Manages allocation and deallocation of memory.
    - Implements virtual memory using paging and swapping.
    - System calls like `mmap()` and `brk()` interact with this subsystem.

 - **File System Management**
    - Provides an interface for reading and writing files.
    - Supports various file systems (ext4, XFS, Btrfs, etc.).
    - Uses system calls such as `open()`, `read()`, `write()`, and `close()`.

 - **Networking Subsystem**
    - Manages network interfaces and protocols.
    - Supports TCP/IP stack for communication over the internet.
    - Uses system calls like `socket()`, `bind()`, and `send()`.


### **2. Architecture-Dependent Components**
- These are specific to a given CPU architecture (e.g., x86, ARM, RISC-V).
- Located in the `arch/` directory of the Linux kernel source tree.
- Handles:
  - CPU-specific instructions
  - Interrupt handling
  - Context switching
  - Power management
  - Low-level boot code

Additionally, **device drivers**, which operate in **kernel space**, can also be architecture-dependent, especially those interacting with hardware at a low level. These include:
- **Platform-Specific Drivers**: Written for specific architectures or hardware configurations.
- **Generic Drivers**: Can work across multiple architectures but require architecture-specific hooks to interact with hardware efficiently.

### What Are Hardware Drivers?
Drivers are special programs that allow the OS to communicate with hardware. Since they interact directly with hardware, they run in **kernel mode**.


### Kernel Structure Diagram

The following diagram illustrates the interaction between kernel subsystems, user space, and hardware:

![Linux Kernel Subsystems](../Images/linux%20Subsystems.png)



