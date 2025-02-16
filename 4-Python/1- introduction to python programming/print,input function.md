## **Python `print()` Function**  

The `print()` function in Python is a **built-in function**, meaning it can be used **without importing** any modules. It is primarily used to **display output** on the console.  

### **Basic Usage**  
We invoke `print()` using **parentheses**, passing the values we want to display as **arguments**:  
```python
print("Hello, World!")
```
**Output:**  
```
Hello, World!
```

---

## **How `print()` Works (Function Execution Flow)**  

When calling `print()`, Python executes the following steps:  
1. **Checks the function name** (`print`) to ensure it is defined.  
2. **Checks the arguments passed** to the function.  
3. **Jumps into the function’s internal implementation** (handled by Python).  
4. **Executes the function**, formatting and displaying the output.  
5. **Returns to the caller (your code)** after execution.  
6. **Resumes execution** from the next line in the script.  

---

## **Passing Multiple Arguments to `print()`**  

We can pass multiple values **separated by commas**, and `print()` automatically separates them with a **space** by default:  
```python
print("Hello", "Python", "World!")
```
**Output:**  
```
Hello Python World!
```

### **Customizing Separators (`sep`)**  
The `sep` parameter changes how multiple arguments are separated:  
```python
print("Hello", "Python", sep="-")
```
**Output:**  
```
Hello-Python
```

---

## **Using `end` to Control Output Formatting**  

By default, `print()` **ends with a newline (`\n`)**, meaning each `print()` call moves to a new line.  
The `end` parameter allows customization:  
```python
print("Hello", end=" ")
print("Python")
```
**Output:**  
```
Hello Python
```
Since `end=" "` replaces the newline, the second `print()` continues on the same line.

Another example:  
```python
print("Loading", end="...")
print("Done!")
```
**Output:**  
```
Loading...Done!
```


## **Printing Special Characters in Strings**  
If we want to print special characters **without interpreting them**, we use **raw strings** by prefixing the string with `r`:  
```python
print(r"C:\Users\Documents\new_folder")
```
**Output:**  
```
C:\Users\Documents\new_folder
```
Without `r`, `\n` would be treated as a newline.

---

## **Using `print()` with Variables**  
We can print variables by passing them as arguments:  
```python
name = "Alice"
age = 25
print("Name:", name, "Age:", age)
```
**Output:**  
```
Name: Alice Age: 25
```

---

## **Python `input()` Built-in Function**  

The `input()` function is used to receive user input from the keyboard. It pauses program execution until the user enters a value and presses **Enter**. By default, it returns the input as a **string**, regardless of the type of data entered.  

### **Basic Usage**  
```python
name = input("Enter your name: ")
print("Hello, " + name + "!")
```
#### **Example Output:**  
```
Enter your name: Alice
Hello, Alice!
```

### **Converting Input to Other Data Types**  
Since `input()` always returns a string, explicit conversion is required when dealing with numbers.  

To get an integer:  
```python
age = int(input("Enter your age: "))
print("Next year, you will be", age + 1)
```
If the user enters `25`, Python converts `"25"` (string) to `25` (integer) and performs the addition.

To get a float:  
```python
height = float(input("Enter your height in meters: "))
print("Your height is", height, "meters.")
```

To get a boolean:  
```python
is_active = bool(input("Are you active? (Enter any text for True, leave empty for False): "))
print("Active status:", is_active)
```
⚠ **Note:** Any non-empty input is considered `True`, while an empty input is `False`.

### **Handling Multiple Inputs**  
Python allows taking multiple inputs on the same line using `.split()`.  
```python
x, y = input("Enter two numbers: ").split()
print("First:", x)
print("Second:", y)
```
#### **Example Input:**  
```
Enter two numbers: 10 20
```
#### **Output:**  
```
First: 10
Second: 20
```
By default, `.split()` separates values using **spaces**, but a custom separator can be specified:  
```python
x, y = input("Enter two numbers separated by a comma: ").split(",")
print("First:", x)
print("Second:", y)
```

To ensure numerical inputs are treated as numbers instead of strings, `map()` is used for conversion.  

```python
x, y = map(int, input("Enter two numbers: ").split())
print("Sum:", x + y)
```
Here’s how `map()` works:  
- `map(int, input().split())` applies `int()` to every value received from `input().split()`.  
- It effectively converts multiple space-separated numbers into integers before assigning them to `x` and `y`.  

For example, if the user enters `10 20`, `map(int, ["10", "20"])` converts `["10", "20"]` into `[10, 20]`, allowing numerical operations like addition.

### **Handling Input Errors Using `try-except`**  
When expecting numbers, users might enter non-numeric values, causing Python to throw an error. Using `try-except`, errors can be handled gracefully instead of crashing the program.  

```python
try:
    number = int(input("Enter a number: "))
    print("You entered:", number)
except ValueError:
    print("Invalid input! Please enter a valid number.")
```

**Syntax Breakdown:**  
- `try:` starts a block of code that might cause an error.  
- `except ValueError:` catches `ValueError`, which occurs if the user enters something that cannot be converted to an integer.  
- If an error occurs inside `try`, execution jumps to `except`, where an error message is displayed instead of crashing.  
- If no error occurs, the `except` block is skipped.  

Without `try-except`, entering text instead of a number would cause:  
```
ValueError: invalid literal for int() with base 10
```
With error handling, the program instead prints:  
```
Invalid input! Please enter a valid number.
```

### **Setting Default Values for `input()`**
Unlike some languages, Python’s `input()` does not support default values. However, a workaround using the **`or` operator** can provide a fallback if the user enters nothing.  

```python
name = input("Enter your name: ") or "Guest"
print("Hello, " + name + "!")
```
#### **How It Works:**  
- If the user **enters a value**, it is stored in `name`.  
- If the user **presses Enter without typing anything**, `name` gets assigned `"Guest"` instead.  

#### **Example Scenarios:**  
```
Enter your name: Alice
Hello, Alice!
```
```
Enter your name: 
Hello, Guest!
```
This technique ensures that an input value is always present, preventing unexpected empty strings.

