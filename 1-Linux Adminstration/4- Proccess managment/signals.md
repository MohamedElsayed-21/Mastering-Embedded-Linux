## Signals & Process 

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