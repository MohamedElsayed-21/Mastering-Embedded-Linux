## **Short-Circuit Evaluation in Bash**  

In Bash, **short-circuit evaluation** allows you to write conditional statements in a single line using `&&` (AND) and `||` (OR).  

### **Syntax:**  
```bash
condition && command_if_true || command_if_false
```
- **`&&`** executes `command_if_true` only if `condition` is **true**.  
- **`||`** executes `command_if_false` only if `condition` is **false**.  

### **Example 1:** File Existence Check  
```bash
[ -f "file.txt" ] && echo "File exists" || echo "File does not exist"
```  
- If `file.txt` **exists**, it prints: `"File exists"`.  
- If `file.txt` **does not exist**, it prints: `"File does not exist"`.  

### **Example 2:** String Comparison  
```bash
name="mohamed"
([ "$name" == "mohamed" ] && echo "Hello $name") || echo "You are not welcome here!!"
```  
- If `name` is `"mohamed"`, it prints: `"Hello mohamed"`.  
- Otherwise, it prints: `"You are not welcome here!!"`.

### **Important Notes:**  
- **Spacing matters in conditionals**: There must be spaces **before and after** `==` inside `[ ]`.  
- **Use quotes around variables** to avoid issues with empty values.  
- For more details, check the manual:  
  ```bash
  man test
  ```  

### **Avoiding Unintended Execution**  
If `command_if_true` fails (returns a non-zero exit status), `command_if_false` will execute. To prevent this, wrap the condition in parentheses:  
```bash
([ -f "file.txt" ] && echo "File exists") || echo "File does not exist"
```
This ensures `"File does not exist"` executes **only** if the condition is false, not if `echo "File exists"` fails.