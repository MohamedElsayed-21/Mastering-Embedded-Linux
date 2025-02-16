# **Conditional Coding in Python**  

## **Syntax of Conditional Statements**  
Conditional coding in Python is done using `if`, `elif`, and `else` statements. The general syntax is:

```python
if condition:
    # Code block executed if condition is True
elif another_condition:
    # Code block executed if the first condition is False, but this one is True
else:
    # Code block executed if none of the above conditions are True
```

Python uses **indentation** (spaces or tabs) to define the code block under each condition.

---

## **Description of Conditional Statements**  

- **`if` Statement**  
The `if` statement is used to execute a block of code **only if** a specified condition is `True`.

- **`elif` (Else If) Statement**  
The `elif` statement allows checking **multiple conditions**. It is used when the first condition is `False`, and we need to check additional conditions.

- **`else` Statement**  
The `else` statement runs **if none of the previous conditions are True**.

- **Nested `if` Statements**  
An `if` statement inside another `if` statement is called a **nested `if`**.

---
### **Common Syntax Errors in Conditional Statements**  

1. **Missing Colon (`:`)** → Every `if`, `elif`, and `else` must end with a colon.  
2. **Incorrect Indentation** → Python requires proper indentation for code blocks.  
3. **Using `elif` or `else` Without `if`** → They must follow an `if` statement.  
4. **Using `=` Instead of `==`** → `=` is assignment, `==` is comparison.  
5. **Multiple `else` Statements** → Only one `else` is allowed in a condition.  