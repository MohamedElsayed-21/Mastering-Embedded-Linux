**# Bash String Operations Documentation**

## **1. Defining Strings in Bash**
Bash allows defining strings using both single and double quotes:
```bash
str1="Hello"
str2='World'
str3="Hello, $str2"  # Using a variable inside a string
```
- **Double quotes (`" "`)** allow variable expansion (`$variable`).
- **Single quotes (`' '`)** treat everything literally (no variable expansion).

---

## **2. Getting String Length**
```bash
str="Hello World"
echo ${#str}  
```
- This returns `11` as the length of "Hello World".

---

## **3. Extracting Substrings**
```bash
str="Hello World"
echo ${str:0:5}   # Extract first 5 characters → "Hello"
echo ${str:6}     # Extract from the 6th character onward → "World"
```
- `${variable:start:length}` extracts part of a string.

---

## **4. Finding & Replacing Strings**
```bash
str="I love Bash scripting"
echo ${str/Bash/Linux}   # Replace first occurrence → "I love Linux scripting"
echo ${str//o/O}         # Replace all 'o' with 'O' → "I lOve Bash scripting"
```
- `${variable/pattern/replacement}` replaces the **first** occurrence.
- `${variable//pattern/replacement}` replaces **all** occurrences.

---

## **5. Checking if a String Contains a Substring**
```bash
str="Hello Bash"
if [[ $str == *"Bash"* ]]; then
    echo "Found"
else
    echo "Not Found"
fi
```
- `[[ $str == *"substring"* ]]` checks if `substring` exists in `str`.

---

## **6. String Concatenation**
```bash
str1="Hello"
str2="World"
str3="$str1 $str2"
echo $str3   # Output: "Hello World"
```
- Strings are concatenated simply by placing them next to each other.

---

## **7. Convert to Uppercase / Lowercase**
```bash
str="Hello World"
echo ${str^^}   # Convert to uppercase → "HELLO WORLD"
echo ${str,,}   # Convert to lowercase → "hello world"
```
- `${variable^^}` converts all characters to uppercase.
- `${variable,,}` converts all characters to lowercase.

---

## **8. Splitting a String by a Delimiter**
```bash
str="apple,banana,grape"
IFS=',' read -ra arr <<< "$str"
echo ${arr[0]}   # "apple"
echo ${arr[1]}   # "banana"
```
- `IFS=','` sets `,` as the delimiter.
- `read -ra arr <<< "$str"` splits the string into an array.

---

## **9. Removing Whitespace from a String**
```bash
str="   Hello World   "
echo "|${str}|"       # |   Hello World   |
echo "|${str// /}|"  # |HelloWorld|
```
- `${variable// /}` removes **all** spaces.

---

## **10. Reversing a String**
```bash
str="Hello"
echo "$str" | rev   # Output: "olleH"
```
- `rev` reverses the input string.

---

## **11. Cutting a String from the Right (Trimming Until a Character)**
```bash
file="backup_2024.tar.gz"
echo "${file%%.*}"   # Output: "backup_2024"
echo "${file%.*}"    # Output: "backup_2024.tar"
```
- `${variable%%pattern}` removes everything **from the first match of pattern from the right**.
- `${variable%pattern}` removes **only the last match**.

---

## **12. Cutting a String from the Right (Keeping the Remainder)**
```bash
file="backup_2024.tar.gz"
echo "${file##*.}"   # Output: "gz"
echo "${file#*.}"    # Output: "tar.gz"
```
- `${variable##pattern}` removes everything **up to the last match from the left**.
- `${variable#pattern}` removes **only the first match from the left**.

---

## **13. Cutting from the Right Using `sed`**
```bash
echo "backup_2024.tar.gz" | sed 's/.*\.//'  
# Output: "gz"
```
- `s/.*\.//` removes **everything before the last dot**.

---

## **14. Cutting from the Right Using `awk`**
```bash
echo "backup_2024.tar.gz" | awk -F'.' '{print $NF}'
# Output: "gz"
```
- `-F'.'` sets `.` as the delimiter.
- `$NF` gets the **last field** after splitting.

---

### **Summary of Methods**

| Operation | Syntax | Description |
|-----------|--------|-------------|
| Get string length | `${#var}` | Returns length of a string |
| Extract substring | `${var:start:length}` | Extracts part of a string |
| Find & replace | `${var/old/new}` | Replaces first match |
| Find & replace all | `${var//old/new}` | Replaces all matches |
| Check if substring exists | `[[ $var == *substring* ]]` | Returns true if found |
| Convert to uppercase | `${var^^}` | Converts string to uppercase |
| Convert to lowercase | `${var,,}` | Converts string to lowercase |
| Split by delimiter | `IFS=',' read -ra arr <<< "$var"` | Splits string into array |
| Remove all spaces | `${var// /}` | Removes spaces |
| Reverse string | `echo "$var" tee rev` |  Reverses the string |
| Remove from right (first match) | `${var%%pattern}` | Removes everything from first match |
| Remove from right (last match) | `${var%pattern}` | Removes everything from last match |
| Remove from left (first match) | `${var#pattern}` | Removes first occurrence from the left |
| Remove from left (last match) | `${var##pattern}` | Removes last occurrence from the left |
| Extract after last `.` | `sed 's/.*\.//'` | Gets last part after `.` |
| Extract after last `.` | `awk -F'.' '{print $NF}'` | Gets last part after `.` |




