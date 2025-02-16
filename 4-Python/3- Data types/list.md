### **Python Lists: Operations & Methods**  

A **list** in Python is an **ordered, mutable collection** that can store multiple data types. Lists are one of the most used data structures in Python.

---

## **Creating Lists**
```python
# Empty list
empty_list = []

# List with elements
numbers = [1, 2, 3, 4, 5]
mixed = [1, "hello", 3.14, True]
nested = [[1, 2], [3, 4]]  # List inside a list
```

---

## **Accessing Elements**
```python
my_list = [10, 20, 30, 40, 50]

print(my_list[0])   # 10 (first element)
print(my_list[-1])  # 50 (last element)
print(my_list[1:4]) # [20, 30, 40] (slicing)
print(my_list[:3])  # [10, 20, 30] (first 3 elements)
print(my_list[::2]) # [10, 30, 50] (step of 2)
```

---

## **Modifying Lists**
Lists are **mutable**, meaning you can modify elements.

```python
my_list = [1, 2, 3, 4]
my_list[2] = 99  # Change the third element
print(my_list)  # [1, 2, 99, 4]
# delete the item in the index 2 and the next item takes index 2
del my_list[2]  # [1, 2, 4]
del my_list[0:2] # [4]
```

---

## **List Operations**
### **🔹 Concatenation (`+`)**
```python
list1 = [1, 2, 3]
list2 = [4, 5, 6]
result = list1 + list2
print(result)  # [1, 2, 3, 4, 5, 6]
```

### **🔹 Repetition (`*`)**
```python
print([0] * 5)  # [0, 0, 0, 0, 0]
```

### **🔹 Membership (`in`)**
```python
print(3 in [1, 2, 3, 4])  # True
print(10 in [1, 2, 3, 4]) # False
```

---

## **Common List Methods**
| Method | Description |
|--------|------------|
| `append(x)` | Adds `x` to the **end** of the list |
| `extend(iterable)` | Adds all elements from `iterable` to the list |
| `insert(index, x)` | Inserts `x` at the specified `index` |
| `remove(x)` | Removes the first occurrence of `x` |
| `pop(index)` | Removes and returns the element at `index` (default last) |
| `index(x)` | Returns the index of `x` |
| `count(x)` | Counts occurrences of `x` |
| `sort()` | Sorts the list in ascending order |
| `reverse()` | Reverses the order of elements |
| `copy()` | Returns a **shallow copy** of the list |
| `clear()` | Removes all elements from the list |

### **Examples**
```python
my_list = [10, 20, 30]

# Append
my_list.append(40)
print(my_list)  # [10, 20, 30, 40]

# Extend
my_list.extend([50, 60])
print(my_list)  # [10, 20, 30, 40, 50, 60]

# Insert
my_list.insert(2, 99)
print(my_list)  # [10, 20, 99, 30, 40, 50, 60]

# Remove
my_list.remove(30)
print(my_list)  # [10, 20, 99, 40, 50, 60]

# Pop
last_element = my_list.pop()
print(last_element)  # 60
print(my_list)  # [10, 20, 99, 40, 50]

# Index
print(my_list.index(40))  # 3

# Count
print(my_list.count(20))  # 1

# Sort
numbers = [4, 1, 3, 2]
numbers.sort()
print(numbers)  # [1, 2, 3, 4]

# Reverse
numbers.reverse()
print(numbers)  # [4, 3, 2, 1]

# Copy
copy_list = my_list.copy()
print(copy_list)  # [10, 20, 99, 40, 50]

# Clear
my_list.clear()
print(my_list)  # []
```

---

## **Looping Through a List**
```python
numbers = [10, 20, 30, 40]

# Using a for loop
for num in numbers:
    print(num)

# Using index
for i in range(len(numbers)):
    print(numbers[i])

# List comprehension (efficient way)
squared = [x**2 for x in numbers]
print(squared)  # [100, 400, 900, 1600]
```


### **List Slicing in Python**  

Slicing allows you to extract a **portion of a list** using this syntax:  
```python
list[start:stop:step]
```
- **`start`** → Index where slicing begins (default = `0`).  
- **`stop`** → Index where slicing ends (**not included**).  
- **`step`** → How many items to skip (default = `1`).  

---

### **Examples**
```python
numbers = [10, 20, 30, 40, 50, 60]
```

- **Basic Slicing**  
```python
print(numbers[1:4])  # Output: [20, 30, 40]  (Indexes 1 to 3)
```

- **Skipping Elements (`step`)**  
```python
print(numbers[::2])  # Output: [10, 30, 50]  (Every 2nd element)
print(numbers[::-1])  # Output: [60, 50, 40, 30, 20, 10] (Reversed list)
```

- **Omitting `start` or `stop`**  
```python
print(numbers[:3])   # Output: [10, 20, 30]  (First 3 elements)
print(numbers[3:])   # Output: [40, 50, 60]  (From index 3 to end)
```

- **Negative Indexing**  
```python
print(numbers[-3:])  # Output: [40, 50, 60]  (Last 3 elements)
print(numbers[:-2])  # Output: [10, 20, 30, 40]  (Exclude last 2 elements)
```

---

## **Copying Lists (Avoid Common Mistake!)**
###  **Incorrect way (creates a reference, not a copy)**
```python
list1 = [1, 2, 3]
list2 = list1  # Both point to the same list
list2.append(4)
print(list1)  # [1, 2, 3, 4] (modified!)
```
### **Correct way (creates a separate copy)**
```python
list1 = [1, 2, 3]
list2 = list1.copy()  # OR list2 = list1[:]
list2.append(4)
print(list1)  # [1, 2, 3] (unchanged)
print(list2)  # [1, 2, 3, 4]
```

---

## **Nested Lists**
A **nested list** is a **list inside another list**. It allows you to store **multi-dimensional data** like tables (2D) or cubes (3D).  

## **2D Lists (Matrix)**
A **2D list** (list of lists) is useful for **grids, tables, or matrices**.

### **Creating a 2D List**
```python
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]
print(matrix[0])   # Output: [1, 2, 3]  (First row)
print(matrix[1][2])  # Output: 6  (Row 1, Column 2)
```
 **Each row is a list** inside the main list.

---

### **🔹 Looping Through a 2D List**
```python
for row in matrix:
    for value in row:
        print(value, end=" ")
# Output: 1 2 3 4 5 6 7 8 9
```

## **3D Lists (Multi-Level Nested Lists)**
A **3D list** is a **list of 2D lists**. Useful for **storing multiple matrices**.

### **Creating a 3D List**
```python
cube = [
    [   # First Matrix
        [1, 2, 3],
        [4, 5, 6]
    ],
    [   # Second Matrix
        [7, 8, 9],
        [10, 11, 12]
    ]
]
print(cube[1])       # Output: [[7, 8, 9], [10, 11, 12]] (Second 2D list)
print(cube[1][0])    # Output: [7, 8, 9] (First row of second matrix)
print(cube[1][0][2]) # Output: 9  (Row 0, Column 2 of second matrix)
```

---

### **🔹 Looping Through a 3D List**
```python
for matrix in cube:
    for row in matrix:
        for value in row:
            print(value, end=" ")
# Output: 1 2 3 4 5 6 7 8 9 10 11 12
```