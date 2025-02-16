# **🔹 Sets in Python**  

A **set** in Python is an **unordered collection** of **unique** elements.  
- **No duplicate values**  
- **Unordered & unindexed**  
- **Fast lookups (uses a hash table)**  
- **Mutable (can be changed after creation)**  

---

## **1️⃣ Creating a Set**  
You can create a set using `{}` or the `set()` function.  

```python
# Using curly braces
my_set = {1, 2, 3, 4, 5}
print(my_set)  # Output: {1, 2, 3, 4, 5}

# Using the set() function
empty_set = set()  #  Correct way to create an empty set
not_a_set = {}  #  This creates an empty dictionary, NOT a set
```

---

## **Properties of Sets**
```python
numbers = {1, 2, 3, 3, 2, 1, 4, 5}
print(numbers)  
# Output: {1, 2, 3, 4, 5}  (Duplicates removed!)
```
 **No duplicates** – Set **automatically removes repeated values**.  

---

## **Adding & Removing Elements**
```python
s = {1, 2, 3}

s.add(4)  # Add an element
print(s)  # Output: {1, 2, 3, 4}

s.remove(2)  # Remove a specific element (Error if not found)
print(s)  # Output: {1, 3, 4}

s.discard(10)  # No error if element doesn't exist
print(s)  # Output: {1, 3, 4}

s.clear()  # Remove all elements
print(s)  # Output: set()
```

---

## **Set Operations**
Python sets support **mathematical operations** like **union, intersection, and difference**.

### **Union (`|` or `.union()`)**
Combines two sets (removes duplicates).  
```python
a = {1, 2, 3}
b = {3, 4, 5}

print(a | b)  # Output: {1, 2, 3, 4, 5}
print(a.union(b))  # Same output
```

---

### **Intersection (`&` or `.intersection()`)**
Finds common elements between sets.  
```python
print(a & b)  # Output: {3}
print(a.intersection(b))  # Same output
```

---

### **Difference (`-` or `.difference()`)**
Elements in **A but not in B**.  
```python
print(a - b)  # Output: {1, 2}
print(a.difference(b))  # Same output
```

---

### **Symmetric Difference (`^` or `.symmetric_difference()`)**
Elements in **either A or B**, but **not both**.  
```python
print(a ^ b)  # Output: {1, 2, 4, 5}
print(a.symmetric_difference(b))  # Same output
```

---

## **Checking Membership (`in` and `not in`)**
```python
s = {1, 2, 3, 4}
print(3 in s)   # Output: True
print(10 in s)  # Output: False
```

---

## **Looping Through a Set**
```python
s = {10, 20, 30}
for num in s:
    print(num)
```
⚠ **Order is not guaranteed!**  

---

## **Frozen Sets (Immutable Sets)**
A **frozen set** is a set that **cannot be modified** after creation.  
```python
frozen_s = frozenset([1, 2, 3, 4])
# frozen_s.add(5)  # ❌ Error! Frozen sets are immutable
print(frozen_s)  # Output: frozenset({1, 2, 3, 4})
```
