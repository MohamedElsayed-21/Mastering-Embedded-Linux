## **Functions in Python**

### **Syntax of a Function**
A function in Python is defined using the `def` keyword followed by a function name, parentheses `()` containing optional parameters, and a colon `:` to indicate the function body.

```python
def function_name(parameters):
    """Docstring explaining the function"""
    # Function body (code)
    return value  # Optional return statement
```

### **Function Arguments**
A function can accept different types of arguments:
- **Positional Arguments**: Passed in the same order as parameters are defined.
- **Keyword Arguments**: Explicitly specify parameter names.
- **Default Arguments**: Have predefined values.
- **Arbitrary Arguments (`*args`)**: Accept multiple positional arguments as a tuple.
- **Arbitrary Keyword Arguments (`**kwargs`)**: Accept multiple keyword arguments as a dictionary.

#### **Example of Different Argument Types**
```python
def student_info(name, age=18, *subjects, **details):
    print(f"Name: {name}")
    print(f"Age: {age}")
    print(f"Subjects: {subjects}")  # Stored as a tuple
    print(f"Additional Details: {details}")  # Stored as a dictionary

#when we invoke the function  un the bellow example ,the age will be overwrite by the given value 20
student_info("Ali", 20, "Math", "Physics", city="Cairo", grade="A") 
```
🔹 **Output:**
```
Name: Ali
Age: 20
Subjects: ('Math', 'Physics')
Additional Details: {'city': 'Cairo', 'grade': 'A'}
```

### **Using `*args` to Pass Multiple Arguments**
The `*args` parameter allows passing multiple positional arguments, which are stored as a **tuple**.

```python
def add_numbers(*numbers):
    return sum(numbers)  # Sums all numbers in the tuple

print(add_numbers(1, 2, 3, 4, 5))  # Output: 15
```

### **Passing a List as an Argument**
To pass a list to a function, use the `*` operator to unpack its elements.

```python
def print_students(*students):
    for student in students:
        print(student)

students_list = ["Ahmed", "Sara", "John"]
print_students(*students_list)  # Unpacks the list
```

🔹 **Output:**
```
Ahmed
Sara
John
```
--- 
### **Variable Scope in Functions**
Variables have different scopes depending on where they are defined:

- **Local Variables**: Defined inside a function and cannot be accessed outside.
- **Global Variables**: Defined outside a function and accessible everywhere.
- **Using `global` Keyword**: Allows modifying a global variable inside a function.

```python
x = 10  # Global variable

def modify():
    global x  # Accessing global variable
    x = 20
    print("Inside function:", x)

modify()
print("Outside function:", x)
```
🔹 **Output:**
```
Inside function: 20
Outside function: 20
```

### **`return` Statement**
The `return` statement is used to send a value from a function back to the caller.

```python
def square(num):
    return num * num  # Returns the squared value

result = square(5)
print(result)  # Output: 25
```

- **Without `return`**, the function returns `None` by default.
- A function **can return multiple values** as a tuple.

```python
def calculations(a, b):
    return a + b, a - b, a * b  # Returns a tuple

add, sub, mul = calculations(5, 3)
print(add, sub, mul)  # Output: 8 2 15
```