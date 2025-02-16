# **Dictionaries in Python **  

A **dictionary** (`dict`) in Python is a **collection of key-value pairs**.  
- **Keys** must be unique and immutable (e.g., strings, numbers, tuples).  
- **Values** can be **any data type** (lists, tuples, other dictionaries, etc.).  
- **Fast lookups** (dictionaries use a **hash table** for quick access).  


## **Creating a Dictionary**
You can define a dictionary using **curly braces `{}`** or the `dict()` function.  

```python
# Using curly braces
student = {"name": "Ahmed", "age": 23, "grade": "A"}
print(student)  
# Output: {'name': 'Ahmed', 'age': 23, 'grade': 'A'}

# Using the dict() function
person = dict(name="Sara", age=25, city="Cairo")
print(person)  
# Output: {'name': 'Sara', 'age': 25, 'city': 'Cairo'}
```


## **Accessing Dictionary Values**
### **Using Keys**
```python
student = {"name": "Ahmed", "age": 23, "grade": "A"}
print(student["name"])  # Output: Ahmed
print(student["age"])   # Output: 23
```
 If the key doesn’t exist, Python raises a `KeyError`.  

### **Using `get()` to Avoid Errors**
```python
print(student.get("name"))     # Output: Ahmed
print(student.get("school"))   # Output: None (instead of an error)
```
 You can also set a **default value**:
```python
print(student.get("school", "Not Available"))  # Output: Not Available
```


## **Adding & Updating Dictionary Items**
```python
student["age"] = 24  # Update value
student["city"] = "Cairo"  # Add new key-value pair
print(student)
# Output: {'name': 'Ahmed', 'age': 24, 'grade': 'A', 'city': 'Cairo'}
```


## **Removing Items**
```python
student.pop("grade")  # Removes 'grade' key
print(student)  
# Output: {'name': 'Ahmed', 'age': 24, 'city': 'Cairo'}

del student["city"]  # Deletes 'city' key
print(student)   # Output: {'name': 'Ahmed', 'age': 24}


student.popitem() #delete the last item from the dictionary.
print(student) #Output: {}


student.clear()  # Removes all elements
print(student)  # Output: {}
```


## **Dictionary Operations**
### **Looping Through a Dictionary**
```python
student = {"name": "Ahmed", "age": 23, "grade": "A"}

# Looping through keys
for key in student.keys():
# student.keys() = (["name", "age" ,"grade"])
    print(key, ":", student[key])

# Output:
# name : Ahmed
# age : 23
# grade : A
```

### **Using `.items()` to Get Both Keys and Values**
```python
for key, value in student.items():
    print(f"{key}: {value}")

# Output:
# name: Ahmed
# age: 23
# grade: A
```

### **Using `.keys()` and `.values()`**
```python
print(student.keys())    # Output: dict_keys(['name', 'age', 'grade'])
print(student.values())  # Output: dict_values(['Ahmed', 23, 'A'])
```


## **Dictionary Comprehension**
You can create a dictionary **in one line** using **dictionary comprehension**.
```python
squares = {x: x**2 for x in range(1, 6)}
print(squares)
# Output: {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
```


## **Nested Dictionaries**
Dictionaries can contain **other dictionaries**.
```python
students = {
    "Ahmed": {"age": 23, "grade": "A"},
    "Sara": {"age": 22, "grade": "B"}
}
print(students["Ahmed"]["grade"])  # Output: A
```