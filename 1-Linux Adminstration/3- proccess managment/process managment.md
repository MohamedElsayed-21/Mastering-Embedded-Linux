# Process Management in Linux

## What is a Process?

A process is an instance of a running program. It consists of executable code, data, and system resources. Processes can be created, managed, and terminated based on system and user requirements.

## Process Identifiers

- **PID (Process ID)**: A unique identifier assigned to each process.
- **PPID (Parent Process ID)**: The PID of the parent process that spawned the current process.
- **PGID (Process Group ID)**: Identifies a group of related processes.
- **SID (Session ID)**: Identifies a session, which is a collection of process groups.

## Process Lifecycle

1. **Process Creation**: A process is created using system calls such as `fork()`, `exec()`, or `clone()`.
2. **Process Execution**: The process runs and executes its assigned task.
3. **Process Termination**: A process can terminate normally, be killed by a signal, or crash due to an error.
4. **Process Cleanup**: The kernel releases resources and removes process entries from the process table.

 **Fork & Exec** 
- **fork()**: Creates a new child process by duplicating the parent process. The child gets a copy of the parent's memory and execution state.
- **exec()**: Replaces the current process image with a new one, loading a different program into the same process space.


**Process vs Thread**
- **Process**: A separate instance of a program with its own memory space, So Processes require inter-process communication (IPC) to communicate with other  process.
- **Thread**: A lightweight execution unit within a process, sharing memory with other threads in the same process , threads can communicate through shared memory.


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


## Process Types

1. **Interactive Process**: Started by a user and interacts with the user (e.g., a text editor or terminal session).
2. **Automated Process (Batch)**: Executed without user interaction, often scheduled using tools like `cron` or `at`.
3. **Daemon Process**: Runs in the background, handling tasks like logging, network requests, and system maintenance.

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

### Automatic (Scheduled) and Batch Jobs
**at**
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

### Crontab File Format
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

---

## Daemon Processes

A daemon is a background process that runs continuously without user interaction. It is commonly used for system services like logging, scheduling tasks, and network communication.

### Characteristics of a Daemon Process
- Runs in the background.
- Has no controlling terminal.
- Typically started at boot time.
- Detached from the parent shell.

### Creating a Daemon Process
A process can become a daemon by following these steps:
1. **Fork the process** to create a child.
2. **Exit the parent process** so that the child is orphaned and adopted by `init`.
3. **Change session ID** using `setsid()` to detach from the terminal.
4. **Change working directory** to avoid locking filesystems.
5. **Close standard input/output/error** to prevent accidental interaction.

### Managing Daemon Processes
Depending on the init system, daemon management differs:

#### System V Init (SysV)
- Uses `/etc/init.d/` scripts for daemon control.
- Commands include:
  - `service <daemon> start|stop|restart|status`
  - `chkconfig <daemon> on|off`

#### systemd
- Uses `.service` unit files for daemons.
- Commands include:
  - `systemctl start <daemon>`
  - `systemctl stop <daemon>`
  - `systemctl restart <daemon>`
  - `systemctl enable <daemon>`


--- 


## Monitoring Processes

Monitoring processes is crucial for system administration, performance tuning, and troubleshooting. Linux provides various tools to monitor CPU usage, memory consumption, disk I/O, and process states.

### Process Monitoring Tools

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

---


## Signals & Process Control

### What is a Signal?

A signal is a notification sent to a process to indicate an event. Signals can be categorized into two types:

#### Termination Signals

| Signal    | Number | Description                                                    |
| --------- | ------ | -------------------------------------------------------------- |
| `SIGTERM` | 15     | Gracefully terminates a process (default for `kill`).          |
| `SIGKILL` | 9      | Forcefully terminates a process (cannot be ignored or caught). |
| `SIGINT`  | 2      | Interrupts a process, typically sent by `Ctrl+C`.              |
| `SIGHUP`  | 1      | Hangup signal, often used to restart daemons.                  |

#### Control & Debugging Signals

| Signal    | Number | Description                                                           |
| --------- | ------ | --------------------------------------------------------------------- |
| `SIGSTOP` | 19     | Suspends a process (equivalent to `Ctrl+Z`).                          |
| `SIGCONT` | 18     | Resumes a suspended process (`fg` or `bg`).                           |
| `SIGTSTP` | 20     | Stops a process from the terminal (`Ctrl+Z`).                         |
| `SIGUSR1` | 10     | User-defined signal for custom handling.                              |
| `SIGUSR2` | 12     | Another user-defined signal.                                          |
| `SIGSEGV` | 11     | Segmentation fault, occurs when a process accesses restricted memory. |
| `SIGALRM` | 14     | Timer signal used for scheduling tasks.                               |
| `SIGCHLD` | 17     | Sent to a parent when a child process terminates.                     |

### Signal Commands

- `kill -l` → Lists all signals.
- `kill <pid>` → Sends `SIGTERM (15)` to terminate a process.
- `kill -<signalNumber> <pid>` → Sends a specific signal.
- `killall <command>` → Sends a signal to all instances of a command.
- `pkill -u <username>` → Sends `SIGTERM` to all processes owned by a user.
- `trap '<command>' <signal>` → Defines a custom signal handler in scripts.













