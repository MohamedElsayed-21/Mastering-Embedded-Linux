### **Escape Sequences in Python**
Escape sequences in Python are special character combinations used inside strings to represent characters that are difficult or impossible to type directly. They start with a **backslash (`\`)** followed by a character.

### **Common Escape Sequences in Python:**
| Escape Sequence | Description | Example | Output |
|----------------|------------|---------|--------|
| `\'` | Single quote | `print('It\'s Python!')` | `It's Python!` |
| `\"` | Double quote | `print("He said \"Hello\"")` | `He said "Hello"` |
| `\\` | Backslash | `print("C:\\Users\\Admin")` | `C:\Users\Admin` |
| `\n` | Newline | `print("Hello\nWorld")` | ```Hello```<br>```World``` |
| `\t` | Tab (adds a space equivalent to a tab) | `print("Hello\tWorld")` | `Hello   World` |
| `\r` | Carriage return (moves cursor to start of line) | `print("Hello\rWorld")` | `World` |
| `\b` | Backspace (removes the previous character) | `print("Hello\bWorld")` | `HellWorld` |
| `\f` | Form feed (used in some printers) | `print("Hello\fWorld")` | `Hello` (form feed effect) `World` |
| `\v` | Vertical tab | `print("Hello\vWorld")` | `Hello` (vertical space) `World` |
| `\ooo` | Octal value | `print("\110\145\154\154\157")` | `Hello` |
| `\xhh` | Hexadecimal value | `print("\x48\x65\x6C\x6C\x6F")` | `Hello` |

### **Raw Strings (`r''` or `r""`)**
To ignore escape sequences, use a raw string by adding `r` before the string:

```python
print(r"C:\Users\Admin")  # Output: C:\Users\Admin
```

