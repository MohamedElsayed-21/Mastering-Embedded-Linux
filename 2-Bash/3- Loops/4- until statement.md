# **Understanding `until`  in Bash**

The `until` loop in Bash is another control flow structure that allows you to repeatedly execute a block of commands **as long as a specified condition is false**. The loop terminates when the condition becomes true. This is the opposite of the `while` loop, which continues as long as the condition is true.

## **Basic Syntax:**

```bash
until condition; do
  commands
done
```
* **`until condition`**: This is the start of the loop. The `condition` is a command or a series of commands whose exit status is evaluated.
* **`;`**: A semicolon (or a newline) is required to separate the `condition` from the `do` keyword.
* **`do commands`**: This is the block of one or more commands that will be executed repeatedly.
* **`done`**: This marks the end of the `until` loop.

## **How it Works:**

1.  **Condition Evaluation:** When the `until` loop is encountered, Bash first evaluates the `condition`.
2.  **Loop Execution:**
    * If the exit status of the `condition` is **non-zero** (indicating failure or "false" in the context of `until`), the commands within the `do...done` block are executed.
    * After the commands are executed, the `condition` is evaluated again.
    * This process repeats until the exit status of the `condition` is **zero** (indicating success or "true").
3.  **Loop Termination:** Once the `condition` evaluates to true (exit status 0), the loop terminates, and the script proceeds with the commands following the `done` keyword.

**Key Differences from `while` Loops:**

* **Condition Logic:** `while` loops continue as long as the condition is true; `until` loops continue as long as the condition is false.
* **Use Cases:** `until` loops are often used when you want to keep trying an operation until it succeeds or wait for a specific state to be reached.

## **Simple Examples:**

* **Waiting for a file to exist:**

    ```bash
    file_to_check="my_file.txt"
    until [ -f "$file_to_check" ]; do
      echo "Waiting for '$file_to_check' to be created..."
      sleep 5
    done
    echo "The file '$file_to_check' now exists. Continuing."
    ```

    In this example, the loop will keep checking if `my_file.txt` exists. It will print a message and wait for 5 seconds in each iteration until the `[ -f "$file_to_check" ]` condition (which returns true if the file exists) becomes true.

* **Retrying a command until success:**

    ```bash
    attempt=0
    max_attempts=3
    until ping -c 1 example.com > /dev/null 2>&1 || (( attempt >= max_attempts )); do
      (( attempt++ ))
      echo "Ping failed (attempt $attempt of $max_attempts). Retrying in 2 seconds..."
      sleep 2
    done

    if (( attempt <= max_attempts )); then
      echo "Ping successful after $attempt attempts."
    else
      echo "Ping failed after $max_attempts attempts."
    fi
    ```

    Here, the loop tries to ping `example.com`. The loop continues as long as the ping fails (exit status is non-zero) OR the number of attempts has not reached the maximum. The `||` (OR) allows the loop to terminate if either the ping succeeds or the maximum attempts are reached.

* **Decrementing a counter until it reaches zero:**

    ```bash
    count=5
    until (( count == 0 )); do
      echo "Count is: $count"
      (( count-- ))
    done
    echo "Count has reached zero."
    ```

    The loop continues as long as `count` is not equal to 0. In each iteration, `count` is decremented.

## **Controlling `until` Loops:**

Just like `while` and `for` loops, you can use `break` and `continue` to control the execution of `until` loops:

* **`break`:** Immediately exits the `until` loop, even if the condition is still false.
* **`continue`:** Skips the remaining commands in the current iteration and goes back to evaluate the condition.

## **Common Mistakes with `until` Loops:**

1. **Condition Never Becoming True:** The most common mistake is writing a condition that never evaluates to true, leading to an infinite loop. Always ensure that the variables involved in the condition are being modified within the loop in a way that will eventually satisfy the termination condition.
2. **Incorrect Logic:** Confusing the logic of `until` with `while` can lead to unexpected behavior. Remember that `until` continues as long as the condition is *false*.
3. **Forgetting to Update Variables:** Similar to `while` loops, forgetting to update variables within the loop that are part of the condition will likely result in an infinite loop.