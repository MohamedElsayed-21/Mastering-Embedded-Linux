# **Understanding `while` in Bash**

The `while` loop in Bash repeats a block of code as long as a specific condition evaluates to **true**. However, in Bash scripting, **conditions** are evaluated based on their **exit status**:

## **The basic syntax is:**

```bash
while [ condition ]
do
    # Commands to execute
done
```

Or alternatively:

```bash
while [[ condition ]]; do
    # Commands to execute
done
```
- **condition** is evaluated before each iteration of the loop.
- If the exit status of the **condition** is `0` (which means true), the loop continues to run.
- If the exit status is **non-zero** (which means false), the loop stops.


So, the **condition** itself is evaluated and gives an **exit status**, and it’s the exit status that determines if the loop continues or terminates.

### **Clarifying the Condition and Exit Status**
When we write a `while` loop like this:
```bash
count=1
while [ $count -le 5 ]
do
    echo "Count is $count"
    ((count++))
done
```
The condition `[ $count -le 5 ]` is checked. The **exit status** of this condition is:

- **`0` (true)** if `$count` is less than or equal to `5`.
- **Non-zero (false)** once `$count` exceeds `5`.

As long as the exit status of the condition is `0`, the loop continues to run. When the exit status becomes non-zero (i.e., when `$count` is greater than `5`), the loop will stop.
Sure! Let’s continue with the detailed explanation on the topics you mentioned.

---

## **Using Conditions with `while`**

In Bash, you can use different types of conditions to control the flow of the `while` loop. These conditions are used to evaluate whether the loop should continue or terminate.

### **1. Single Square Brackets `[ ]`**

In Bash, the single square brackets `[ ]` are used for testing conditions within `while` loops, but it's important to note that they are a part of the test command (`test`), and they have certain limitations compared to `[[ ]]`.



#### **Key Features of `[ ]`**

1. **Numeric Conditions**
    You can compare numbers using conditional expressions like :
    - `-eq` (equal)
    - `-ne` (not equal)
    - `-gt` (greater than)
    - `-lt` (less than)
    - `-ge` (greater than or equal)
    - `-le` (less than or equal)

    Example:
    ```bash
    count=1
    while [ $count -le 5 ]
    do
        echo "Count is $count"
        ((count++))
    done
        ```
    This loop continues as long as `$count` is less than or equal to 5.

2. **String Conditions**
     You can compare strings using :
    - `=` (equal)
    - `!=` (not equal)
    - `-z` (string is empty)
    - `-n` (string is not empty)

    Example:
    ```bash
    input=""
    while [ "$input" != "exit" ]
    do
        read -p "Type something (type 'exit' to quit): " input
        echo "You typed: $input"
    done
    ```
    The loop continues as long as the user doesn't type "exit".

3. **File Conditions**

    Bash allows you to check if files or directories exist using conditions like :
    - `-e` (file exists)
    - `-f` (regular file)
    - `-d` (directory)
    - `-s` (file exists and is not empty)
    - `-r` (readable)
    - `-w` (writable)
    - `-x` (executable)

    Example:
    ```bash
    while [ ! -f "important_file.txt" ]
    do
        echo "Waiting for important_file.txt to exist..."
        sleep 1
    done
    echo "File exists! Continuing..."
    ```

    This loop will keep running until the file `important_file.txt` exists.


### **2. Double Square Brackets `[[ ]]`**
In bash`[[ ]]` is a more powerful version of the traditional single square brackets `[ ]` for conditional expressions. It’s a **Bash-specific** feature, meaning it's not available in all shells (like `sh` or `dash`). It provides enhanced functionality, which makes it the preferred choice in Bash scripts.


#### **Key Features of `[[ ]]`**
1. **Pattern Matching**

   - With `[[ ]]`, you can use **wildcards** to match patterns, which is much more convenient than using the `*` operator with `[ ]`. For example:
        ```bash
        filename="myfile.txt"
        if [[ $filename == *.txt ]]; then
            echo "It's a text file."
        fi
        ```
   In this example, `*.txt` checks if the `filename` ends with `.txt`. You can use `*`, `?`, and `[...]` for pattern matching.

2. **Regex Matching**

    -  `[[ ]]` supports **regular expression** matching with the `=~` operator. This allows you to test whether a string matches a regex pattern:
        ```bash
        string="hello123"
        if [[ $string =~ [0-9]+ ]]; then
            echo "The string contains digits."
        fi
        ```
   Here, `[0-9]+` is a regular expression that checks if there are one or more digits in the string.
   
3. **Logical Operators and Grouping**

    - Inside `[[ ]]`, you can combine multiple conditions using logical operators like `&&` (AND) and `||` (OR). This makes it easier to construct complex conditional expressions.Parentheses can be used to group expressions, which helps in structuring logical tests clearly.

    - In this example, we’ll check two conditions using **`&&`** (AND) and **`||`** (OR) inside `[[ ]]`, along with parentheses for grouping.
        ```bash
        x=5
        y=10
        z=20

        # Using AND (&&) to combine conditions
        if [[ $x -lt 10 && $y -gt 5 ]]; then
            echo "Both conditions are true: x is less than 10 AND y is greater than 5."
        fi

        # Using OR (||) to combine conditions
        if [[ $x -lt 10 || $z -gt 15 ]]; then
            echo "At least one condition is true: x is less than 10 OR z is greater than 15."
        fi

        # Grouping conditions using parentheses
        if [[ ($x -lt 10 && $y -gt 5) || $z -gt 15 ]]; then
            echo "Either both x is less than 10 AND y is greater than 5, or z is greater than 15."
        fi

        ```

4. **Improved Syntax and Error Handling**

   - With `[[ ]]`, you don’t need to worry as much about word splitting or pathname expansion. This means you can often use variables without extensive quoting, reducing potential errors.
   - The syntax is more forgiving, which helps in writing cleaner and more reliable scripts.

    - Example: Handling Variables with Spaces Without Extensive Quoting
        ```bash
        #!/bin/bash     
        # Variables with spaces
        dir_name="My Folder"
        file_name="My File.txt"     
        # With [ ] - Might lead to unexpected issues if not quoted
        if [ -d $dir_name ]; then  # Without quotes, it could cause issues if the variable contains spaces
            echo "Directory exists."
        else
            echo "Directory does not exist."
        fi     
        # With [[ ]] - No need for extensive quoting
        if [[ -d $dir_name ]]; then  # No issues even without quotes
            echo "Directory exists."
        else
            echo "Directory does not exist."
        fi
        ```
5. **Built-in Safety**

   - Since `[[ ]]` is built into Bash, it bypasses some of the limitations and unexpected behaviors that can occur with `[ ]`. This includes better handling of unset or empty variables, leading to fewer runtime errors.
     ```bash
      # Example 1: Handling an unset variable
      unset my_var
  
      # Using [ ] - This could cause an error if the variable is unset
      if [ $my_var == "hello" ]; then
          echo "Variable is set to hello"
      else
          echo "Variable is not set to hello"
      fi
  
      # Using [[ ]] - No error even if the variable is unset
      if [[ $my_var == "hello" ]]; then
          echo "Variable is set to hello"
      else
          echo "Variable is not set to hello"
      fi
  
      # Example 2: Handling an empty variable
      my_empty_var=""
  
      # Using [ ] - This could lead to an error if the variable is empty (e.g., if not quoted)
      if [ $my_empty_var == "hello" ]; then  # Potential problem if the variable is empty
          echo "Empty variable is set to hello"
      else
          echo "Empty variable is not set to hello"
      fi

     ```
6. **Direct Evaluation of Expressions**

   - While arithmetic evaluations are often performed using `(( ))`, `[[ ]]` allows for more direct testing of conditions, making it a good fit for many conditional checks in scripts.
   ```bash
    #!/bin/bash

    # Simple example showing direct expression evaluation in [[ ]] vs [].

    num=10

    echo "Using [[ ]]:"
    while [[ "$num" -gt 5 && "$num" -ne 7 ]]; do
    # Directly checks if num is greater than 5 AND not equal to 7.
    echo "Number is: $num"
    num=$((num - 1))
    done
    echo ""
    num=10
    echo "Using []:"
    while [ "$num" -gt 5 ] && [ "$num" -ne 7 ]; do
    # Requires separate checks with [ ] joined by shell '&&'.
    echo "Number is (using []): $num"
    num=$((num - 1))
    done
    echo "Done."
   ```

### **3.`(( ))` in Bash is for arithmetic evaluation.**

**As a `while` condition:**
 - The expression inside `(( ))` is evaluated arithmetically.
 - The `while` loop continues as long as the evaluation result is **non-zero**.
 - If the result is **zero**, the loop stops.

#### **Key Features of `(( ))`**
1. **Arithmetic focus:** Designed for math operations (`+`, `-`, `*`, `/`, `++`, `--`, etc.).
2. **Variable shorthand:** Often no need for `$` with variables inside.
3. **Integers only:** Handles integer arithmetic.
4. **Counting loops:** Very useful for loops with counters.

**example:**
```bash
counter=0
while (( counter < 3 )); do
  echo "Counter: $counter"
  (( counter++ ))
done
```

### **In summary** `[]`, `[[]]`, and `(( ))`**
  - `[ ]`: Traditional test command (less features)
  - `[[ ]]`: More advanced test command (supports regex, string patterns)
  - `(( ))`: For arithmetic evaluations


## Infinite `while` Loops 
- Infinite loops run forever if their condition is always true.
- Used for continuous processes. Common forms:
    ```bash
    while true; do ... done 
    while :; do       # ':' is a built-in command that always succeeds (returns true)
    while [[ 1 ]]; do # Any non-empty string or non-zero number is often treated as true
    ```
**Exiting:** `Ctrl + C`, `break` statement, external signals.

## **Nested `while` Loops in Bash**

A **nested `while` loop** is a `while` loop placed inside another `while` loop. This allows you to perform more complex operations by iterating over multiple sets of data. The outer loop will iterate through its conditions, and for each iteration of the outer loop, the inner loop will execute.

### **Structure of Nested `while` Loops:**

```bash
while [ condition1 ]
do
    # Outer loop body

    while [ condition2 ]
    do
        # Inner loop body
    done

done
```

Here, the outer loop will keep iterating as long as `condition1` is true, and for each iteration of the outer loop, the inner loop will continue iterating as long as `condition2` is true.

### **Example: Nested `while` Loops**

Let’s say we want to print a multiplication table. For each number from 1 to 5 (outer loop), the inner loop will iterate from 1 to 10 and print the result of multiplying the outer loop number by the inner loop number.

```bash
# Outer loop for numbers 1 to 5
outer=1
while [ $outer -le 5 ]
do
    echo "Multiplication table for $outer:"
    
    # Inner loop for numbers 1 to 10
    inner=1
    while [ $inner -le 10 ]
    do
        result=$((outer * inner))
        echo "$outer * $inner = $result"
        ((inner++))  # Increment inner loop variable
    done
    
    ((outer++))  # Increment outer loop variable
    echo  # Blank line between tables
done
```

## Common Mistakes 
1.  **Forgetting to Update Loop Variable:** Leads to infinite loops. Debug by checking the condition and using `set -x`.
    ```bash
    i=0
    while [[ "$i" -lt 5 ]]; do echo "$i"; done # Error!
    ```
2.  **Incorrect Loop Condition:** Off-by-one errors, wrong operators.

    ```bash
    count=1
    while [[ "$count" -lt 5 ]]; do echo "$count"; count=$((count + 1)); done # Runs 4 times
    ```
3.  **Command Substitution in Condition:** Be aware if the command's output changes unexpectedly.
4.  **Misusing `break` and `continue`:** Can lead to incorrect loop behavior.
5.  **Ignoring Edge Cases:** Consider initial conditions and unexpected variable states.