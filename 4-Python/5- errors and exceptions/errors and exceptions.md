
### **Types of Errors in Python**  

Python errors can be categorized into **syntax errors** and **exceptions (runtime errors).**  

---

## **1. Syntax Errors** (`SyntaxError`)  
These occur when the code violates Python's syntax rules.  
🔹 **Example:**  
```python
if True  # Missing colon  ':'  -> leds to SyntaxError 

    print("Hello") 
```

## **2. Exceptions (Runtime Errors)**  
Exceptions occur **while the program is running** and cause it to crash unless handled.  

### **Exception Types**  
Python provides a set of built-in exceptions to handle different runtime errors.  

### **1. Arithmetic Errors**
| Exception | Cause |
|-----------|-------|
| `ZeroDivisionError` | Division or modulo by zero |
| `FloatingPointError` | Issues with floating-point calculations (rare) |
| `OverflowError` | Number too large for Python to handle |

### **2. Attribute and Type Errors**
| Exception | Cause |
|-----------|-------|
| `AttributeError` | Accessing a missing attribute in an object |
| `TypeError` | Using an operation on an incompatible type |

### **3. Indexing and Key Errors**
| Exception | Cause |
|-----------|-------|
| `IndexError` | Accessing an out-of-range index in a sequence (list, tuple, etc.) |
| `KeyError` | Accessing a missing key in a dictionary |

### **4. Input and Output Errors**
| Exception | Cause |
|-----------|-------|
| `EOFError` | Unexpected end of input (e.g., `input()` with no input) |
| `FileNotFoundError` | Trying to open a file that does not exist |
| `PermissionError` | Trying to access a file without permission |
| `IsADirectoryError` | Opening a directory as a file |
| `NotADirectoryError` | Treating a file as a directory |

### **5. Import and Name Errors**
| Exception | Cause |
|-----------|-------|
| `ImportError` | Importing a module that does not exist |
| `ModuleNotFoundError` | Module not found (subclass of `ImportError`) |
| `NameError` | Using an undefined variable |

### **6. Memory and Recursion Errors**
| Exception | Cause |
|-----------|-------|
| `MemoryError` | Running out of memory |
| `RecursionError` | Exceeding recursion limit |

### **7. Syntax and Indentation Errors**
| Exception | Cause |
|-----------|-------|
| `SyntaxError` | Invalid Python syntax |
| `IndentationError` | Incorrect indentation |
| `TabError` | Mixing spaces and tabs in indentation |

### **8. Value and Type Conversion Errors**
| Exception | Cause |
|-----------|-------|
| `ValueError` | Passing an invalid value to a function |
| `UnicodeDecodeError` | Error decoding Unicode |
| `UnicodeEncodeError` | Error encoding Unicode |
| `UnicodeTranslateError` | Error translating Unicode |

### **9. Iteration and Generator Errors**
| Exception | Cause |
|-----------|-------|
| `StopIteration` | Raised when an iterator has no more elements |
| `StopAsyncIteration` | Raised when an asynchronous iterator has no more elements |

### **10. System-Related Errors**
| Exception | Cause |
|-----------|-------|
| `OSError` | General operating system errors (file handling, process management, etc.) |
| `SystemError` | Internal Python error (should not occur in normal use) |
| `RuntimeError` | Generic runtime error when no specific exception fits |

### **11. Other Exceptions**
| Exception | Cause |
|-----------|-------|
| `AssertionError` | Raised when `assert` statement fails |
| `NotImplementedError` | Raised when an abstract method is not implemented |
| `KeyboardInterrupt` | Raised when the user interrupts execution (e.g., `Ctrl+C`) |

---

## **How to Handle Errors?**

**`try` and `except` in Python (Exception Handling)**  

## **Syntax of `try-except`**  
```python
try:
    # Code that might raise an error
except ExceptionType:
    # Code to handle the error
except (ExceptionType , ExceptionType): 
    # if you want to handle two types of errors in the same way you can do this syntax
    # Code to handle the error

```

## **Description of `try-except`**  

- The `try` block contains **code that may cause an exception** (runtime error).  
- If an error occurs, Python **stops execution** and jumps to the `except` block.  
- The `except` block **handles the error**, preventing the program from crashing.  

---

## **Full Syntax with Additional Features**  

```python
try:
    # Code that may raise an exception
except ExceptionType as e:
    # Handle specific exception
else:
    # Executes if no exception occurs
finally:
    # Executes no matter what (cleanup code)
```

### **Explanation**
1. **`try` Block** → Contains code that might cause an exception.  
2. **`except` Block** → Handles specific errors if they occur.  
3. **`else` Block** *(Optional)* → Runs if no exception occurs.  
4. **`finally` Block** *(Optional)* → Runs **always**, useful for cleanup (e.g., closing files).  


## **Example: Handling Multiple Errors**
```python
try:
    x = int(input("Enter a number: "))
    print(10 / x)
except ZeroDivisionError:
    print("You cannot divide by zero!")
except ValueError:
    print("Invalid input! Please enter a number.")
except Exception as e:
    print(f"Unexpected error: {e}")
```

## **Example: Using `else` and `finally`**
```python
try:
    file = open("data.txt", "r")
    content = file.read()
except FileNotFoundError:
    print("File not found!")
else:
    print("File read successfully!")
finally:
    file.close()  # Ensures file closes even if an error occurs
```
---

### **Manually Raising Exceptions in Python**  

 You can manually raise exceptions in Python using the `raise` statement.  

## **Syntax of `raise`**  
```python
raise ExceptionType("Custom error message")
```
- `ExceptionType` → The type of exception to raise (e.g., `ValueError`, `TypeError`).  
- `"Custom error message"` → Optional message describing the error.  

## ** Example Raising a Generic Exception**  
```python
raise Exception("Something went wrong!")
```
Output: `Exception: Something went wrong!`  

---
### **`assert` Keyword in Python (Assertions)**  

The `assert` statement is used for **debugging** and **validating conditions** in Python. It checks whether an expression is `True`, and if it's `False`, it raises an `AssertionError`.  

## **Syntax of `assert`**  
```python
assert condition, "Optional error message"
```
- **`condition`** → The expression that must be `True`.  
- **`"Optional error message"`** → (Optional) Custom message displayed if the assertion fails.  

## **Example of Using `assert`**  

### **Basic Assertion**
```python
x = 10
assert x > 5  # Passes (No error)
assert x < 5  # Fails
```
Output: `AssertionError` (because `x < 5` is `False`).  

## **Important Notes**
1. **Assertions are removed in optimized mode (`python -O script.py`)**, so do **not** use them for critical error handling.  
2. Use `try-except` for handling errors in production instead of `assert`.