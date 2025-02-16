# **The `while` Loop in Python**  

## **Syntax of `while` Loop**  
```python
while condition:
    # Code block executed repeatedly as long as condition is True
```

---

## **Description of `while` Loop**  

- The `while` loop **executes a block of code repeatedly** as long as the given condition is `True`.  
- The condition is checked **before** each iteration.  
- If the condition **becomes False**, the loop stops.  
- It is used when **the number of iterations is unknown** beforehand.  
- To prevent an **infinite loop**, the condition should eventually become `False`.

---

## **Common Errors in `while` Loop**  

1. **Forgetting to Update the Condition** → Leads to an infinite loop.  
2. **Incorrect Indentation** → Causes an `IndentationError`.  
3. **Using `=` Instead of `==`** → Mistakenly assigning a value instead of checking a condition.  
4. **Forgetting the Colon (`:`)** → Causes a `SyntaxError`.  
