# Performance analysis Task
## System Call Use Case
Imagine you’re a software architect encountering performance issues in your software. To address these, you decide to gain insights from the system. You discover that various commands in user space serve similar purposes but may differ in performance. Examples include:
- ls vs. find
- cp vs. rsync
- diff vs. cmp
- sort vs. uniq
- grep vs. sed

## Main Tasks
### - Time Measurement
Measure the execution time for each command to assess performance.
### -System Interaction Identification
Identify which system stack (e.g., file system, network) each command interacts with during execution.
### - Syscall Time Breakdown
Break down the total execution time of each command into time per system call to understand resource consumption.
### -Performance Evaluation
Analyze results to determine which command performs better based on execution time, system interaction, and syscall breakdown.





# Solution 

## Time Measurement and System Analysis.

- Performance evaluation of similar commands is conducted under identical conditions, with each command configured to perform the same task as its counterpart for fair comparison.
### Time Measurement using `time` Command 
#### The time command provides: 
- **real**: The total time it took from starting the command to when it finished.
- **user**: The time the CPU spent running the command itself (its actual logic).
- **sys**: The time the CPU spent in kernel mode performing operations.

## System Interaction Identification.
- Using `strace -c -e trace=file,memory,network,process <command>`, we track interactions with the file system, memory, network, and processes. 
## Syscall Time Breakdown.
- The `strace -c <command>` tool breaks down the time spent on each system call, highlighting resource-intensive operations.




## **`ls` Vs `find`**

### `ls`    

```bash
time ls -R 
```
```Terminal_output 
real	0m0.003s
user	0m0.000s
sys	    0m0.003s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.
Interacts with the file system to read file information and with memory to handle data during the process.

### `find`
```bash
time find .
```

```Terminal_output 
real	0m0.003s
user	0m0.002s
sys	    0m0.001s
```
### **Performance Evaluation** 
#### `ls` is faster since it lists files in the current directory, requiring fewer resources.
#### `find` is slower due to its recursive search and more complex system interactions.


#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.
Interacts with the file system to search files and directories and with memory to load data during the search process.


## **`cp` Vs `rsync`**

### `cp`  

```bash
time cp  ./source/* ./destination/
```
```Terminal_output 
real    0m0.007s
user    0m0.003s
sys     0m0.004s
```

#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`. `brk()`.
#### Network: Not used.
Interacts with the file system for copying files and with memory during the copying process.

### `rsync`
```bash
time rsync -a ./source/ ./destination/

```
```Terminal_output 
real	0m0.050s
user	0m0.005s
sys	    0m0.010s
```

#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`. `brk()`.
#### Network: `socket()`, `connect()`, `socketpair()`.
Interacts with the file system for file transfers, memory for managing data, and network for communication between devices over the network.



### **Performance Evaluation** 
#### `cp` performs better for local file copying as it involves only file system and memory operations.
#### `rsync` is slower due to network interactions but is better suited for file synchronization and transfers over a network.





## **`diff` VS `cmp`**
### `diff`
```bash
time diff file1.txt file2.txt 
```

```Terminal_output 
1,2c1,2
< file 1 text
< This is a test
---
> file 2 text
> This is a demo

real	0m0.003s
user	0m0.000s
sys 	0m0.003s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.

Interacts with the file system to compare files and with memory for managing data during the process.

### `cmp` 
```bash
time cmp file1.txt file2.txt

```
```Terminal_output 
file1.txt file2.txt differ: byte 6, line 1

real	0m0.003s
user	0m0.000s
sys	    0m0.002s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`. `brk()`.
Interacts with the file system to compare files and with memory to load data during the comparison.

### **Performance Evaluation** 
#### `cmp` is faster for comparing files byte by byte with fewer resources.
#### `diff` is more resource-intensive due to detailed comparison and file processing.

## **`sort` Vs `uniq`**

### `sort`
```bash
time sort file1.txt
```

```Terminal_output 
apple
apple
apple
banana
grape
orange
orange

real	0m0.003s
user	0m0.001s
sys	    0m0.002s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`. `brk()`.
Interacts with the file system to read data from files and with memory to manage data during the sorting process.


### `uniq`
```bash
time uniq file1.txt
```

```Terminal_output 
apple
banana
orange
grape
orange
apple

real	0m0.002s
user	0m0.000s
sys 	0m0.002s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.
Interacts with the file system to process files and with memory to manage data while removing duplicates.


### **Performance Evaluation** 
#### `uniq` is faster as it only removes duplicates without sorting the data.
#### `sort` is slower due to the overhead of sorting the data before processing.



## **`grep` Vs `sed`**

### `grep`

```bash
time grep "apple" file1.txt
```

```Terminal_output 
apple
apple
apple

real	0m0.003s
user	0m0.001s
sys	    0m0.002s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.
Interacts with the file system to search files and with memory to load data and perform the search.

### `sed`
```bash
time sed 's/apple/fruit/' file1.txt
```

```Terminal_output 
fruit
banana
orange
grape
orange
fruit
fruit

real	0m0.003s
user	0m0.001s
sys	    0m0.001s
```
#### File System: `openat()`, `newfstatat()`, `access()`.
#### Memory: `mmap()`, `munmap()`, `mprotect()`.

Interacts with the file system to edit files and with memory to perform modifications during the process.


### **Performance Evaluation** 
#### `grep` is more efficient for searching text, as it doesn’t modify the file.
#### `sed` is slower due to its modification of file contents, but it's more powerful for text manipulation.


