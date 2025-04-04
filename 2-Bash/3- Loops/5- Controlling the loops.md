# Controlling the Loop
Bash provides commands to control the flow of execution within a loop: `break` and `continue`.

## **`break`:**
The `break` command immediately terminates the current loop (the innermost loop if nested) and transfers control to the command following the loop.
**Example:**

```bash
for i in 1 2 3 4 5; do
  if [[ "$i" -eq 3 ]]; then
    echo "Breaking the loop at i = $i"
    break
  fi
  echo "Current value of i: $i"
done
echo "Loop finished."
```


**Output:**

```
Current value of i: 1
Current value of i: 2
Breaking the loop at i = 3
Loop finished.
```
**`break` in `while`:**

```bash
counter=0
while [[ "$counter" -lt 5 ]]; do
  if [[ "$counter" -eq 3 ]]; then
    echo "Breaking the while loop at counter = $counter"
    break
  fi
  echo "Counter: $counter"
  (( counter++ ))
done
echo "While loop finished."
```

## **`continue`:**
The `continue` command skips the rest of the commands within the current iteration of the loop and proceeds to the next iteration. The loop condition is then re-evaluated.

**Example:**

- **`continue` in `for`:**
```bash
for i in 1 2 3 4 5; do
  if [[ "$i" -eq 3 ]]; then
    echo "Skipping iteration at i = $i"
    continue
  fi
  echo "Current value of i: $i"
done
echo "Loop finished."
```

**Output:**
```terminal
Current value of i: 1
Current value of i: 2
Skipping iteration at i = 3
Current value of i: 4
Current value of i: 5
Loop finished.
```

- **`continue` in `while`:**

```bash
counter=0
while [[ "$counter" -lt 5 ]]; do
  (( counter++ ))
  if [[ "$counter" -eq 3 ]]; then
    echo "Skipping iteration in while loop at counter = $counter"
    continue
  fi
  echo "Counter: $counter"
done
echo "While loop finished."
```