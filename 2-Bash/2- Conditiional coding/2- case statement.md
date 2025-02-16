# ****`case`** Statement Documentation in BASH **

## **Overview**

The `case` statement in Bash is a control structure used to execute different blocks of code based on pattern matching. It is a cleaner and more efficient alternative to multiple `if-elif-else` conditions when handling a fixed set of options.

---

## **Syntax of **`case`** Statement**

A `case` statement follows this general structure:

```bash
case variable in
    pattern1)  
        # Commands to execute if pattern1 matches  
        ;;
    pattern2|pattern3)  
        # Commands to execute if pattern2 or pattern3 matches  
        ;;
    *)  
        # Default case if none of the patterns match  
        ;;
esac
```

Each case pattern is terminated by `;;`, and `esac` marks the end of the `case` block.

---

## **Pattern Matching in ****`case`**

Unlike `if` conditions, `case` uses pattern matching instead of exact comparisons. Common pattern matching symbols include:

- `*` → Matches zero or more characters.
- `?` → Matches exactly one character.
- `[abc]` → Matches any single character inside the brackets.
- `[a-z]` → Matches any lowercase letter within the specified range.

### **Example:**

```bash
read -p "Enter a letter: " letter

case $letter in
    a) echo "You entered 'a'";;
    b|c) echo "You entered 'b' or 'c'";;
    [d-f]) echo "You entered a letter between d and f";;
    ?) echo "You entered a single character";;
    *) echo "Unknown input";;
esac
```

---

## **Extended Pattern Matching**

By default, `case` does not support complex regex patterns. However, Bash allows enabling extended pattern matching using:

```bash
shopt -s extglob  # Enable advanced pattern matching
export LC_COLLATE=C # to enable case sensitive in REGEX .
```

Extended pattern matching operators include:

- `@(pattern1|pattern2|pattern3)` → Matches one of the patterns.
- `!(pattern)` → Matches anything except the specified pattern.
- `?(pattern)` → Matches zero or one occurrence.
- `*(pattern)` → Matches zero or more occurrences.
- `+(pattern)` → Matches one or more occurrences.

### **Example:**

```bash
shopt -s extglob  # Enable advanced pattern matching

read -p "Enter a filename: " file

case $file in
    *.@(jpg|png|gif)) echo "This is an image file";;
    *.@(mp4|mkv|avi)) echo "This is a video file";;
    !(*.*)) echo "This file has no extension";;
    *) echo "Unknown file type";;
esac
```

---

## **Performance Considerations**

- `case` is generally **faster** than multiple `if` conditions when checking against multiple fixed values. It is faster and more readable compared to multiple if conditions
- `if` statements are better suited for **complex numerical comparisons** or logical evaluations.

### **Performance Comparison Example**

Using `if`:

```bash
if [ "$var" = "apple" ] || [ "$var" = "banana" ] || [ "$var" = "cherry" ]; then
    echo "Fruit detected"
fi
```

Using `case`:

```bash
case $var in
    apple|banana|cherry) echo "Fruit detected";;
esac
```

The `case` version is cleaner and more efficient.

