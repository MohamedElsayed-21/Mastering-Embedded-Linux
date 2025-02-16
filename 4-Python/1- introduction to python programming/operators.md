
## **Arithmetic Operations in Python**
Python supports a variety of **arithmetic operators**, categorized into **unary, binary, and shortcut (compound) operators**.

---

### **Unary Operators (Single Operand)**
- **Operate on only one value.**  
- Common unary operators:  
  - **`+` (Unary plus)** → No effect, returns the same value.  
  - **`-` (Unary minus)** → Negates the value (changes the sign).  
  - **`~` (Bitwise NOT)** → Inverts all bits (`~x = -(x+1)`).  

#### **Examples:**
```python
x = 5
print(+x)  # 5 (No effect)
print(-x)  # -5 (Negation)
print(~x)  # -6 (Bitwise NOT, flips bits)
```

---

### **Binary Operators (Two Operands)**
- **Operate on two values (left & right operands).**
- Used for arithmetic, comparison, and bitwise operations.

#### **Arithmetic Binary Operators:**
| Operator | Description | Example | Output |
|----------|------------|---------|--------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `10 - 4` | `6` |
| `*` | Multiplication | `6 * 2` | `12` |
| `/` | Division (float) | `10 / 3` | `3.3333` |
| `//` | Floor Division | `10 // 3` | `3` |
| `%` | Modulus (remainder) | `10 % 3` | `1` |
| `**` | Exponentiation | `2 ** 3` | `8` |

#### **Example:**
```python
a = 10
b = 3

print(a + b)   # 13
print(a - b)   # 7
print(a * b)   # 30
print(a / b)   # 3.3333
print(a // b)  # 3
print(a % b)   # 1
print(a ** b)  # 1000
```

---

### **Shortcut (Compound Assignment) Operators**
Shortcut (also called **compound assignment**) operators combine arithmetic and assignment operations in one step.

| Operator | Equivalent To | Example |
|----------|--------------|---------|
| `+=` | `x = x + y` | `x += 5` |
| `-=` | `x = x - y` | `x -= 3` |
| `*=` | `x = x * y` | `x *= 2` |
| `/=` | `x = x / y` | `x /= 4` |
| `//=` | `x = x // y` | `x //= 2` |
| `%=` | `x = x % y` | `x %= 3` |
| `**=` | `x = x ** y` | `x **= 2` |

#### **Example:**
```python
x = 10
x += 5   # Equivalent to x = x + 5
print(x) # Output: 15

x *= 2   # Equivalent to x = x * 2
print(x) # Output: 30
```

---

### **Order of Operations (PEMDAS Rule)**
Python follows the **PEMDAS** order for arithmetic evaluation:
1. **Parentheses `()`** – Highest priority  
2. **Exponentiation `**`**  
3. **Multiplication `*`, Division `/`, Floor Division `//`, Modulus `%`**  
4. **Addition `+`, Subtraction `-`**  

#### **Example:**
```python
result = 10 + 3 * 2  # 10 + (3 * 2) = 16
print(result)
```

# **String Operators and Comparison Operators in Python**  

---

## **1. String Operators**  

Python provides several operators for manipulating strings.

### **Concatenation (`+`)**
Used to join two or more strings together.
```python
str1 = "Hello"
str2 = "Python"
result = str1 + " " + str2
print(result)  # Output: Hello Python
```

### **Repetition (`*`)**
Repeats a string multiple times.
```python
text = "Ha"
print(text * 3)  # Output: HaHaHa
```

### **Membership Operators (`in`, `not in`)**
Used to check if a substring exists within a string.
```python
message = "Hello Python"
print("Python" in message)   # True
print("Java" not in message) # True
```

### **String Indexing (`[]`)**
Used to access characters in a string by index.
```python
text = "Python"
print(text[0])   # P
print(text[-1])  # n
```

### **String Slicing (`[:]`)**
Used to extract a portion of a string.
```python
text = "Python"
print(text[0:4])  # Pyth
print(text[::-1]) # nohtyP (Reversed string)
```

---

## **2. Comparison Operators**  

Comparison operators in Python compare two values and return **True or False**.

| Operator | Description | Example | Output |
|----------|------------|---------|--------|
| `==`     | Equal to | `"hello" == "Hello"` | False |
| `!=`     | Not equal to | `"Python" != "Java"` | True |
| `>`      | Greater than (Lexicographically) | `"banana" > "apple"` | True |
| `<`      | Less than | `"apple" < "banana"` | True |
| `>=`     | Greater than or equal to | `"car" >= "car"` | True |
| `<=`     | Less than or equal to | `"apple" <= "banana"` | True |

### **Example of String Comparison**
```python
print("apple" == "Apple")  # False (case-sensitive)
print("apple" > "banana")  # False (a < b in ASCII)
print("Python" != "Java")  # True
```

### **How String Comparison Works**
- Python compares strings based on their **Unicode (ASCII) values**.
- **Lowercase letters have higher values than uppercase letters** (`"a" > "Z"`).
- **Lexicographic order** is followed (like dictionary order).

```python
print(ord("a"))  # 97
print(ord("A"))  # 65
print("a" > "A")  # True
```
