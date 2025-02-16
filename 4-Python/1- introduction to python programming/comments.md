## **Comments in Python**  
A **comment** is a part of the code that is ignored by the Python interpreter. Comments are used to explain code, make it more readable, and prevent execution of certain lines.

---

### **Single-Line Comments (`#`)**  
In Python, single-line comments start with the `#` symbol. Everything after `#` on the same line is ignored by the interpreter.

#### **Example:**
```python
# This is a single-line comment
x = 10  # Assigning 10 to variable x
print(x)  # Printing x
```

---

### **Multi-Line Comments**
Python **does not have a dedicated multi-line comment syntax** like `/* */` in other languages. However, you can achieve multi-line comments using one of the following methods:

#### **Option 1: Consecutive `#` Symbols**
```python
# This is a multi-line comment
# that spans multiple lines
# using multiple `#` symbols.
```

#### **Option 2: Using Triple Quotes (`'''` or `"""`)**  
Although triple quotes are mainly used for **multi-line strings**, they can also be used as a workaround for multi-line comments. However, they are still **considered string literals** and are not technically ignored by the interpreter.

```python
"""
This is a multi-line comment.
Python treats this as a string, but if it's not assigned to a variable,
it is ignored at runtime.
"""
print("Hello, World!")
```
or
```python
'''
Another way to write
multi-line comments using
triple single quotes.
'''
```

⚠ **Important Note:**  
Using triple quotes (`'''` or `"""`) **is not an official comment**—it is a string literal that is not assigned to a variable. If placed within a function or a class, Python **does not ignore it** but stores it as a **docstring**.

---

### **Docstrings (`""" """`) – Not a Comment**
Python provides **docstrings** for documenting functions, classes, and modules. Unlike comments, docstrings are stored as part of the function or class metadata and can be accessed using `help()`.

#### **Example:**
```python
def add(a, b):
    """This function returns the sum of two numbers."""
    return a + b

print(add(5, 3))
print(help(add))  # Shows the docstring
```

