## **Variables in Python**  
A **variable** in Python is a name used to store a value in memory. Unlike statically typed languages, Python does **not require explicit declaration** of variables, as it is **dynamically typed**. This means the type of a variable is determined at runtime based on the assigned value.  

---

## **Declaring and Assigning Variables**  
Variables in Python are assigned using the `=` operator. The right-hand side contains the value, which is then stored in the variable on the left-hand side.  

### **Example:**  
```python
x = 10         # Integer
name = "John"  # String
pi = 3.14      # Float
is_active = True  # Boolean
```

### **Dynamic Typing in Python**  
Python allows you to change the type of a variable by reassigning it to a new value.  

```python
x = 5      # x is an integer
x = "Hello"  # Now x is a string
x = 3.14   # Now x is a float
```
To check the type of a variable, use the `type()` function:  

```python
x = 10
print(type(x))  # Output: <class 'int'>

y = "Python"
print(type(y))  # Output: <class 'str'>
```

---

## **Variable Naming Rules**  

### **Valid Variable Naming Rules:**  
1. **Must start with a letter (`a-z`, `A-Z`) or an underscore (`_`).**  
2. **Cannot start with a number (`0-9`).**  
3. **Can only contain letters, numbers, and underscores (`_`).**  
4. **Cannot use Python reserved keywords.**  
5. **Case-sensitive (e.g., `Name` and `name` are different variables).**  

### **Examples of Valid and Invalid Variable Names:**  

####  **Valid Names:**  
```python
age = 25
_name = "Alice"
user1 = "Bob"
user_name = "Charlie"
```

####  **Invalid Names:**  
```python
1name = "Alice"  #  Cannot start with a number
user-name = "Bob"  #  Cannot contain hyphens
class = "Python"  #  Cannot use reserved keywords
```

### **Python Reserved Keywords (Cannot Be Used as Variable Names)**  
Python has a set of **reserved words** that cannot be used as variable names because they are part of the language syntax.  

| and | as | assert | break | class | continue | def | del |  
| --- | -- | ------ | ----- | ----- | -------- | --- | --- |  
| elif | else | except | False | finally | for | from | global |  
| if | import | in | is | lambda | None | nonlocal | not |  
| or | pass | raise | return | True | try | while | with |  
| yield |  

If you try to use one of these keywords as a variable name, Python will raise a **SyntaxError**.  

```python
class = 10  # SyntaxError: invalid syntax
```

---

## **Multiple Variable Assignment**  
Python allows assigning values to multiple variables in a **single line**.  

```python
a, b, c = 5, "Hello", 3.5
print(a)  # Output: 5
print(b)  # Output: Hello
print(c)  # Output: 3.5
```

### **Assigning the Same Value to Multiple Variables:**  
```python
x = y = z = 100
print(x, y, z)  # Output: 100 100 100
```

---

## **Constants in Python**  
Python does not have built-in constants, but by convention, variables that should not change are written in **uppercase**.  

```python
PI = 3.14159
GRAVITY = 9.81
```
Although this does not **prevent modification**, it is a convention that signals to other developers that the variable should remain unchanged.  

```python
PI = 3.14  # Allowed, but not recommended
```

---
## **Deleting Variables**  
Python allows you to delete a variable using the `del` statement. Once deleted, trying to access the variable will raise a **NameError**.  

```python
x = 100
del x
print(x)  #  NameError: name 'x' is not defined
```

---

## **Variable Scope (Global vs. Local)**  
### **Local Variables**
- Declared **inside a function** and accessible only within that function.  

```python
def my_function():
    local_var = "I am local"
    print(local_var)

my_function()
# print(local_var)  #  NameError: local_var is not defined
```

### **Global Variables**
- Declared **outside functions** and accessible from anywhere in the script.  

```python
global_var = "I am global"

def my_function():
    print(global_var)  # Accessible inside the function

my_function()
print(global_var)  # Accessible outside the function
```

### **Using the `global` Keyword**
If you want to modify a **global** variable inside a function, you must use the `global` keyword.  

```python
count = 0  # Global variable

def update_count():
    global count
    count += 1  # Modify global variable

update_count()
print(count)  # Output: 1
```

---

## **Checking if a Variable Exists**
You can check if a variable exists using the `globals()` or `locals()` functions.  

```python
x = 10

print("x" in globals())  # True (x exists globally)
print("y" in locals())   # False (y is not defined locally)
```

---

