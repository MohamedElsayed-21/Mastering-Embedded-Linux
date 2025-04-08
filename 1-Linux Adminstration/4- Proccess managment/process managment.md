# Process Management in Linux

## What is a Process?

- A process is an instance of a running program. It consists of executable code, data, and system resources. Processes can be created, managed, and terminated based on system and user requirements.
- A process is an abstract entity defined by the kernel, which allocates system resources to execute a program.

## What is a Program ?
**program** is a file containing information on how to create a process at runtime.  

**Contents of a program file:**  
- **Binary format identification:** Specifies the format of the executable file, enabling the kernel to interpret it (e.g., ELF in modern UNIX/Linux).  
- **Machine-language instructions:** Encode the program’s algorithm.  
- **Program entry-point address:** Indicates where execution should start.  
- **Data:** Includes initial variable values and constants (e.g., strings).  
- **Symbol and relocation tables:** Describe function and variable locations, used for debugging and dynamic linking.  
- **Shared-library and dynamic-linking information:** Lists required shared libraries and the dynamic linker.  
- **Other information:** Additional details necessary for constructing a process.

#### A single **program** can be used to create multiple **processes**, meaning many processes can run the same program.  

### From the **kernel’s perspective**, a process consists of:  
- **User-space memory** containing program code and variables.  
- **Kernel data structures** that store process-related information,
In the kernel there is a data structure called task_struct defined in [sched.h](https://elixir.bootlin.com/linux/v6.13.6/source/include/linux/sched.h#L661) that forms the basis of implementing processes and threads alike. This data structure captures scheduling-related information, identifiers  including:  
  - Process **IDs**  
    - **PID (Process ID)**: A unique identifier assigned to each process.
      **Notes:** 
       - There is no fixed relationship between a program and its PID (except for system processes like init with PID 1).
       - When the PID counter reaches 32,767, it resets to 300 (instead of 1) to avoid conflicts with system processes.
       - Adjustable PID Limit: In Linux 2.6 and later, the limit of 32,767 can be modified using /proc/sys/kernel/pid_max, supporting up to 4 million PIDs on 64-bit systems.

    - **PPID (Parent Process ID)**: The PID of the parent process that spawned the current process.
      **Notes:** 
        - The Parent Process ID (PPID) represents the hierarchical relationship between processes. Every process has a parent (except `init`).
        - If a parent process terminates, its orphaned child process is adopted by `init` (`PID 1`).
        - The parent of a process can be found in `/proc/PID/status` under the Ppid field.
    - **PGID (Process Group ID)**: Identifies a group of related processes.
    - **SID (Session ID)**: Identifies a session, which is a collection of process groups.
  - **Virtual memory tables**  
  - **Open file descriptors**  
  - **Signal handling information**  
  - **Resource usage and limits**  
  - **Current working directory**  
  - Other necessary details.

## Process States

| State                         | Description                                                                          |
| ----------------------------- | ------------------------------------------------------------------------------------ |
| **R (Running/Ready)**         | The process is either executing or ready to execute.                                 |
| **S (Sleeping)**              | The process is waiting for an event to occur.                                        |
| **D (Uninterruptible Sleep)** | The process is waiting for I/O and cannot be interrupted.                            |
| **T (Stopped)**               | The process is suspended, often by `SIGSTOP`.                                        |
| **Z (Zombie)**                | The process has terminated but is waiting for its parent to collect its exit status. |
| **X (Dead Process)**          | Only visible in rare cases on certain systems.                                       |
| **< (High Priority)**         | Indicates a high-priority process.                                                   |
| **N (Low Priority)**          | Indicates a low-priority process.                                                    |

## Process Lifecycle

1. **Process Creation**: A process is created using system calls such as `fork()`, `exec()`, or `clone()`.
2. **Process Execution**: The process runs and executes its assigned task.
3. **Process Termination**: A process can terminate normally, be killed by a signal, or crash due to an error.
4. **Process Cleanup**: The kernel releases resources and removes process entries from the process table.

![Linux process states](../Images/Linux%20process%20states%20.png)


## Process Types
- **Interactive Process**: Started by a user and interacts with the user (e.g., a text editor or terminal session).
- **Automated Process (Batch)**: Executed without user interaction, often scheduled using tools like `cron` or `at`.
- **Daemon Process**: Runs in the background, handling tasks like logging, network requests, and system maintenance.

### 1. Interactive Process
it is a process that requires user input and provides immediate output. It runs in the foreground, interacting directly with the user through a terminal or GUI. Examples include command-line tools like `vim`, `nano`, and `top`. These processes can be paused (using `Ctrl + Z`), resumed (`fg`), or sent to the background (`bg`).

### 2. Automatic (Scheduled) and Batch Jobs
- **at**
  - `at -f <job-to-run> <day> <hour>:<min>` → Schedules a job at a specific time.
  - `atq` → Displays the list of scheduled jobs.
  - `at -r <n>` or `atrm <n>` → Removes job number `n`.

**batch**
  - `batch <job-to-run>` → Runs a job when system load permits.

 **Cron Jobs**
  - `vi /etc/crontab` → Edits the system-wide crontab file.
  - `crontab -e` → Edits user-specific crontab file.
  - `crontab -l` → Displays the crontab file.
  - `crontab -r` → Removes the user’s crontab file.

#### Crontab File Format
A crontab file consists of lines defining scheduled tasks. Each line follows this format:
```
* * * * * command-to-be-executed
- - - - -
| | | | |
| | | | +---- Day of the week (0 - 7) [Both 0 and 7 represent Sunday]
| | | +------ Month (1 - 12)
| | +-------- Day of the month (1 - 31)
| +---------- Hour (0 - 23)
+------------ Minute (0 - 59)
```
Each field can contain:
- A single number (e.g., `5` for 5th minute/hour/day, etc.).
- A range (e.g., `1-5` for first to fifth minute/hour/day, etc.).
- A step value (e.g., `*/5` for every 5 minutes).
- A list (e.g., `1,15,30` for execution at specific times).
- `*` for all possible values.

Special strings can also be used for predefined events:
- `@reboot` → Runs a command at system startup.
- `@yearly` or `@annually` → Runs once a year.
- `@monthly` → Runs once a month.
- `@weekly` → Runs once a week.
- `@daily` or `@midnight` → Runs once a day.
- `@hourly` → Runs once an hour.
- `@poweron` → Runs a command when the system powers on.

- Example of a crontab entry:
  ```
  0 3 * * * /path/to/script.sh  # Runs a script every day at 3 AM
  ```

### Daemon Processes

A daemon is a background process that runs continuously without user interaction. It is commonly used for system services like logging, scheduling tasks, and network communication.

#### Characteristics of a Daemon Process
- Runs in the background.
- Has no controlling terminal.
- Typically started at boot time.
- Detached from the parent shell.

#### Creating a Daemon Process
A process can become a daemon by following these steps:
1. **Fork the process** to create a child.
2. **Exit the parent process** so that the child is orphaned and adopted by `init`.
3. **Change session ID** using `setsid()` to detach from the terminal.
4. **Change working directory** to avoid locking filesystems.
5. **Close standard input/output/error** to prevent accidental interaction.

#### Managing Daemon Processes
Depending on the init system, daemon management differs:

-  **System V Init (SysV)**
   - Uses `/etc/init.d/` scripts for daemon control.
   - Commands include:
     - `service <daemon> start|stop|restart|status`
     - `chkconfig <daemon> on|off`

- **systemd**
  - Uses `.service` unit files for daemons.
  - Commands include:
    - `systemctl start <daemon>`
    - `systemctl stop <daemon>`
    - `systemctl restart <daemon>`
    - `systemctl enable <daemon>`


--- 

## Process Commands

### Viewing Processes

- `pstree` → Displays a tree of processes.
- `pstree -p` → Shows processes with their IDs.
- `jobs` → Lists active background jobs.
- `ps aux` → Displays detailed information about all running processes.
- `ps -ef` → Similar to `ps aux`, but with a different column format.

### Controlling Processes

- `Ctrl + Z` → Pauses the current process.
- `fg` → Resumes a paused process in the foreground.
- `bg` → Resumes a paused process in the background.
- `kill %n` → Terminates a job with job number `n`.
- `kill <pid>` → Sends `SIGTERM` to terminate a process.
- `kill -9 <pid>` → Forcefully terminates a process using `SIGKILL`.


### Monitoring ProcessesTools

Monitoring processes is crucial for system administration, performance tuning, and troubleshooting. Linux provides various tools to monitor CPU usage, memory consumption, disk I/O, and process states.
1. **`top`**: Provides a dynamic real-time view of system processes, including CPU and memory usage.
2. **`htop`**: An interactive process viewer with a more user-friendly interface than `top`.
3. **`ps`**: Lists running processes with various filtering and formatting options.
4. **`free`**: Displays available and used system memory.

### Process Management and Resource Control

1. **Setting Process Priorities**:

   - `nice -<value> <process-id>` → Sets a process priority (-19 is highest, 20 is lowest).
   - `renice <value> <process-id>` → Changes priority of a running process.

2. **Memory and Resource Usage**:

   - `free -h` → Displays memory usage in human-readable format.
   - `free -s 1` → Updates memory usage every second.
   - `vmstat 1 10` → Monitors CPU, memory, and I/O statistics over 10 seconds.
   - `ulimit -a` → Displays resource limits for the current shell session.

3. **Viewing Detailed Process Information**:
   - `ps aux` → BSD-style standard for displaying all processes with details.
   - `ps -elf` → System V-style standard for listing all processes with extended details.
   - `ps auxf | more` → Displays process list page by page.
   - `ps -o pid,ppid,pgid,sid,user,command` →  `-o <info> ` Shows specfic process info. 
   - `ps -H` → Displays process threads.

By using these tools and commands, administrators can effectively monitor and manage processes to optimize system performance and troubleshoot issues.
