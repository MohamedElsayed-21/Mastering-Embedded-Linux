# **Conditional Statements in Bash**

## **Understanding `if` Conditions in Bash**

`if` conditions in Bash are used to execute a block of code only if a certain condition is met. If the condition evaluates to **true**, the script executes the block inside the `if`. If it's **false**, the block is skipped.

---

## **Structure of an `if` Statement**

An `if` statement consists of:

- **A condition**: The expression that determines if the block executes.
- **A command block**: Executed if the condition is `true`.
- **The `fi` keyword**: Marks the end of the `if` statement.

---

## **`else` and `elif` in Bash**

- **`else`**: Executes if the condition in `if` is false.
- **`elif`** (else if): Allows multiple conditions in a single `if` statement.

### **Example**

```bash
if [ condition ]; then
    # This block executes if condition is true
elif [ another_condition ]; then
    # This block executes if the first condition is false but this one is true
else
    # This block executes if all conditions are false
fi
```

**Spaces around `[` and `]` are required**, otherwise the script will fail.

---

## **Condition Types in Bash**

### **String Comparison**

| Operator | Description           |
| -------- | --------------------- |
| `=`      | Strings are equal     |
| `!=`     | Strings are not equal |
| `-z`     | String is empty       |
| `-n`     | String is not empty   |

#### **Syntax for String Comparison**

```bash
if [ "$string1" = "$string2" ]; then
    echo "Strings are equal"
fi

if [ -z "$var" ]; then
    echo "Variable is empty"
fi

if [ -n "$var" ]; then
    echo "Variable is NOT empty"
fi
```

---

### **Numeric Comparison** *(Only works inside `[ ]` and not with strings)*

| Operator | Description              |
| -------- | ------------------------ |
| `-eq`    | Equal to                 |
| `-ne`    | Not equal to             |
| `-gt`    | Greater than             |
| `-lt`    | Less than                |
| `-ge`    | Greater than or equal to |
| `-le`    | Less than or equal to    |

#### **Example for Numeric Comparison**

```bash
if [ "$num1" -gt "$num2" ]; then
    echo "num1 is greater than num2"
fi
```

---

### **Conditional Operators for String Matching**

| Example                | Description                                                     |
| ---------------------- | --------------------------------------------------------------- |
| `[[ "abcd" = *bc* ]]`  | Checks if `abcd` contains `bc` (true)                           |
| `[[ "abc" = ab[cd] ]]` | Checks if the third character of `abc` is `c` or `d` (true)     |
| `[[ "abc" > "bcd" ]]`  | Checks if `abc` comes **after** `bcd` lexicographically (false) |
| `[[ "abc" < "bcd" ]]`  | Checks if `abc` comes **before** `bcd` lexicographically (true) |

**Double brackets `[[ ]]` are exclusive to Bash and do not work in other shells.**

#### **Example for String Matching**

```bash
if [[ "$string" = *pattern* ]]; then
    echo "Pattern found in string"
fi
```

---

## **Logical `AND` and `OR` Operators**

You can use **`&&`** (AND) and **`||`** (OR) to combine multiple conditions.

### **Example:**

```bash
if [ condition1 ] && [ condition2 ]; then
    # Executes if both conditions are true
fi
```

```bash
if [[ condition1 || condition2 ]]; then
    # Executes if at least one condition is true
fi
```

Both `[ ]` and `[[ ]]` support these operators, but `[[ ]]` offers more flexibility with pattern matching.

---

## **File Condition Checks**

| Operator | Description                       |
| -------- | --------------------------------- |
| `-e`     | File exists                       |
| `-f`     | File exists and is a regular file |
| `-d`     | Directory exists                  |
| `-r`     | File is readable                  |
| `-w`     | File is writable                  |
| `-x`     | File is executable                |

### **Example :**

```bash
if [ -f "filename" ]; then
    echo "File exists"
fi
```

---
## quick summary 
In **Bash scripting**, `[ ]`, `[[ ]]`, and `(( ))` are used for different types of condition evaluations. Here’s a breakdown of their differences:  

---

### **1. `[ ]` (Single Brackets - `test` command)**
- A **POSIX-compliant** test command.
- Requires **spaces** around operators.
- Supports basic **string** and **integer comparisons**.
- Does **not** support complex conditions like `&&`, `||` inside.

**Example:**  
```bash
[ "$name" == "Mohamed" ] && echo "Hello, Mohamed" || echo "Access denied"
```
- **Important:** Use `=` for string comparison in `[ ]`, but `==` works in some shells.

---

### **2. `[[ ]]` (Double Brackets - Bash Built-in)**
- **Bash-specific** (not POSIX-compliant).
- Supports **advanced string operations**, like pattern matching (`=~`).
- Allows `&&` and `||` inside without escaping.
- Prevents **word splitting** and **globbing**.
- you can use the REGEX here 

**Example:**  
```bash
[[ "$name" == "Mohamed" ]] && echo "Hello, Mohamed" || echo "Access denied"
[[ "hello world" =~ ^hello ]] && echo "Pattern matched"
```
- **Use `=~` for regex matching.**  
- **No need to escape `&&` or `||`.**

---

### **3. `(( ))` (Arithmetic Evaluation)**
- Used **only for numerical expressions**.
- Supports **C-style** arithmetic operations.
- No need for `$` before variables inside `(( ))`.

**Example:**  
```bash
a=5
b=10
(( a < b )) && echo "a is less than b"
```
 **Faster and more readable for numerical conditions.**  
 **Can use `+`, `-`, `*`, `/`, `%`, `++`, `--` directly.**

---

### **Summary**
| Syntax | Used For | Supports | POSIX Compliant |
|--------|---------|----------|----------------|
| `[ ]` | Basic conditions | Strings, Integers |  Yes |
| `[[ ]]` | Advanced conditions | Strings, Pattern Matching |  No |
| `(( ))` | Arithmetic | Integer operations |  No |

 **Use `[ ]` for compatibility**, `[[ ]]` for **better string handling**, and `(( ))` for **math operations**.



## **Common Mistakes in `if` Conditions**

- **Forgetting spaces around `[ ]`**:
  ```bash
  if ["$var"="value"]; then  #  Incorrect: No spaces around `=` and after `[` `]`
  ```
  Correct:
  ```bash
  if [ "$var" = "value" ]; then  #  Correct
  ```

- **Not quoting variables**: If `$var` is empty, the condition may fail unexpectedly.
  ```bash
  if [ $var = "value" ]; then  #  Incorrect: Can cause syntax errors if $var is empty
  ```
  Correct:
  ```bash
  if [ "$var" = "value" ]; then  #  Correct
  ```
