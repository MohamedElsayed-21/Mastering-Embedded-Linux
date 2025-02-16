# **The `for` Loop in Python**  

## **Syntax of `for` Loop**  
```python
for variable in iterable:
    # Code block executed for each item in iterable
```

---

## **Description of `for` Loop**  

- The `for` loop **iterates over a sequence** (list, tuple, string, range, etc.).  
- The loop runs **once for each element** in the sequence.  
- The **loop variable** takes the value of each element in the iterable.  
- Unlike `while`, a `for` loop is used when the **number of iterations is known**.  

---

## **Common Errors in `for` Loop**  

1. **Forgetting the Colon (`:`)** → Causes a `SyntaxError`.  
2. **Using `=` Instead of `in`** → Incorrect iteration syntax.  
3. **Incorrect Indentation** → Causes an `IndentationError`.  
4. **Modifying the Iterable While Iterating** → Can cause unexpected behavior.  


## **`range()` Function**  

The `range()` function generates a sequence of numbers and is commonly used with `for` loops.  

### **Syntax**
```python
range(start, stop, step)
```
- **`start`** (optional) → Beginning of the sequence (default is `0`).  
- **`stop`** (required) → The sequence **excludes** this value.  
- **`step`** (optional) → The increment/decrement (default is `1`).  

### **Examples**
```python
for i in range(5):  
    print(i)  
# Output: 0 1 2 3 4

for i in range(2, 10, 2):  
    print(i)  
# Output: 2 4 6 8
```

---

## **`break` Statement**  

- `break` **terminates** the loop immediately, even if the condition is still `True`.  

### **Example**
```python
for i in range(10):
    if i == 5:
        break  # Stops loop when i == 5
    print(i)

# Output: 0 1 2 3 4
```

---

## **`continue` Statement**  

- `continue` **skips the current iteration** and moves to the next one.  

### **Example**
```python
for i in range(5):
    if i == 2:
        continue  # Skips when i == 2
    print(i)

# Output: 0 1 3 4
```

---

## **`pass` Statement**  

- `pass` is a **placeholder** when a loop (or any block) needs to be syntactically correct but does nothing.  

### **Example**
```python
for i in range(5):
    if i == 2:
        pass  # Placeholder
    print(i)

# Output: 0 1 2 3 4
```

---

## **`else` in Loops**  

- The `else` block in a loop runs **only if the loop completes without `break`**.  

### **Example**
```python
for i in range(5):
    if i == 3:
        break
    print(i)
else:
    print("Loop completed")

# Output: 0 1 2  (No "Loop completed" because of `break`)
```
