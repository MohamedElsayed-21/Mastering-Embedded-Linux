
# Problem Description

The task involves identifying and fixing a bug in a C++ application. The provided application produces unexpected output, and the objective is to analyze the issue by using the `strace` tool to trace system calls and understand the application's behavior.

# Steps to Solve the Problem
## Step 1: Compile the Application

To begin, compile the C++ application using the g++ compiler. Use the following command:

```bash
g++ Buggy_App.cpp -o Binary
```

This command compiles the source file `Buggy_App.cpp` into an executable binary named `Binary`.

## Step 2: Run the Application

Execute the compiled binary to observe the unexpected behavior. This step helps you understand the current output before debugging.

```bash
./Binary
```

## Step 3: Trace System Calls with strace

Use strace to trace the system calls made by the application. Focus on identifying the system calls with errors (exit value = -1). Use the following command:

```bash
strace ./Binary 2>&1 | grep "= -1"
```

`2>&1` in a shell command means that the standard error output (file descriptor 2) is redirected to the same location as the standard output (file descriptor 1).

`| grep "= -1"` This command filters the strace output to show only the system calls that return an error.

## Step 4: Analyze the strace Output

From the filtered strace output, identify the specific system calls causing issues. For example:

```Terminal_output 
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffe3fc8aea0) = -1 EINVAL (Invalid argument)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "sample.txt", O_RDONLY) = -1 ENOENT (No such file or directory)
```

The `openat` call indicates that the file sample.txt is missing, which is likely the main issue.

## Step 5: Resolve the Issue

To resolve the issue, create a file named sample.txt in the same directory as the binary. Use the following command:


```bash
touch sample.txt
```
## Step 6: Re-compile the cpp code 
Run the binary again to verify that the issue is resolved

```bash
g++ Buggy_App.cpp -o Buggyapp_solved
./Buggyapp_solved
```

