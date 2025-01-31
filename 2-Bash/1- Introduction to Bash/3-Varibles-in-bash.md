#  Variables in Bash Scripting

## Introduction to Variables in Bash
- Variables in Bash are used to store data that can be accessed and manipulated throughout a script.
- They provide flexibility and allow you to write dynamic and reusable scripts.
- A variable is a value that can vary or change.
- A variable always has a **`$`** sign before it's name.
- A variable name may only contain alphanumeric or underscores
- A variable is case sensitive as well.

---

## Types of Variables in Bash

### Local Variables

- Defined within a function and accessible only inside that function.
- Example:
  ```bash
  my_function() {
      local var="I am local"
      echo $var
  }
  ```

### Global Variables

- Default type for variables in Bash. Accessible throughout the script unless redefined locally.
- Example:
  ```bash
  var="I am global"
  echo $var
  ```
### Environment Variables

- Used to pass information from the shell to programs (child processes).
- Example:
  ```bash
  # Exporting a variable makes it available to child processes.
  export PATH=$PATH:/custom/path
  # Access them like regular variables:
  echo $PATH
  ```


---

## Declaring Variables and Data Types Using `declare`

The `declare` command in Bash provides enhanced control over variables and their data types. By combining variable declaration with specific attributes, you can handle different data types effectively in Bash scripting.

### Common Data Types and Their Usage:

**Strings**

- Default type for variables in Bash.
- Example:
  ```bash
  # No spaces around the equal sign
  declare name="Alice"
  echo "Hello, $name!"
  ```

**Integers**

- Use the `-i` option to ensure the variable is treated as an integer.
- Example:
  ```bash
  declare -i num=42
  num+=8
  echo $num  # Output: 50
  ```

**Indexed Arrays**

- Use the `-a` option to declare an indexed array.
- Example:
  ```bash
  declare -a fruits=("apple" "orange" "banana")
  echo ${fruits[0]}  # Output: apple
  ```

**Associative Arrays**

- Use the `-A` option for associative arrays (Bash 4.0+).
- Example:
  ```bash
  declare -A colors
  colors[apple]="red"
  colors[banana]="yellow"
  echo ${colors[apple]}  # Output: red
  ```

**Read-Only Variables**

- Use the `-r` option to make a variable immutable.
- Example:
  ```bash
  declare -r pi=3.14
  echo $pi
  # pi=3.14159  # This will result in an error

  readonly my_var="Immutable"
  my_var="New Value"  # This will result in an error
  ```

**Null Variables**

- Unset variables or explicitly set them to null.
- Example:
  ```bash
  declare my_var
  echo $my_var  # Output: (nothing)
  unset my_var
  ```

---

## Unsetting Variables

The `unset` command removes a variable from the environment.

```bash
var="Temporary"
unset var
echo $var  # Output: (nothing)
```
---

## Accessing Variable Values

- Use the `$` symbol to retrieve the value of a variable.
- Enclose variable names in `{}` for clarity, especially when concatenating or working with complex strings.
  ```bash
  var="World"
  echo "Hello, ${var}!"
  ```

### Why Use `${}` Instead of `$`?

Using `${}` offers several advantages over using `$` alone:

**Avoid Ambiguity**

- Prevents confusion when variables are concatenated with other characters.

  ```bash
  name="John"
  echo "$name123"    # Output: (empty, as $name123 does not exist)
  echo "${name}123"  # Output: John123
  ```

**Special Cases**

- Ensures proper evaluation when accessing array elements or keys in associative arrays.

  ```bash
  declare -a fruits=("apple" "banana")
  echo ${fruits[1]}   # Output: banana

  declare -A colors
  colors[apple]="red"
  echo ${colors[apple]}  # Output: red
  ```

**Escaping Special Characters**

- Avoids issues when dealing with variables that might collide with reserved characters.

  ```bash
  file_name="data"
  echo "Path: ${file_name}.txt"
  ```
**variable substitution with default values**
  ``` bash 

  city="cairo"
  echo ${city="Giza"}    
  # ===> if city is not defined then print Giza so it will print Cairo

  city="cairo"
  echo ${city:="Giza"}  
  # ===> if city variable is not defined then define it and make its value Giza so it will print Cairo because city variable is already defined

  unset city
  echo ${city:="Giza"}   
  # ===> unset deletes the variable city so it will print Giza
  ```

**string manipulation**
  ``` bash 
  long_string="HelloWorld"
  echo ${long_string:0:5}   # Output: Hello (extracts the first 5 characters)
  echo ${long_string:5}     # Output: World (extracts from the 6th character onward)
  ```
---

## Best Practices for Using Variables in Bash

- Use meaningful names for variables.
- Always quote variables to avoid issues with spaces or special characters.
  ```bash
  echo 'Value is: "$var" '
  ```
- Use `declare` for better control over variable attributes.
- Avoid overwriting important environment variables.
- Variable name must be in lower-case with underscore `Var-name` to seprate words .

