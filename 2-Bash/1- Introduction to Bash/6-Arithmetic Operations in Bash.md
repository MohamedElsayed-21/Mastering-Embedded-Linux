# Arithmetic Operations in Bash

Bash supports various arithmetic operations, which can be performed using different methods such as `expr`, `let`, `(( ))`, and `bc`. This document provides an overview of arithmetic operations in Bash and their usage.

## 1. Arithmetic Methods in Bash

### 1.1 Using `expr`
`expr` is one of the oldest methods to perform arithmetic operations in Bash. It requires spaces between numbers and operators.
```bash
#!/bin/bash
A=5
B=3
#for addition   
expr $A + $B
# for subtraction
expr $A - $B
# for division
expr $A / $B
# for multiplication --> Use `\*` instead of `*` for multiplication to avoid wildcard expansion.
expr $A \* $B
result=$(expr $A + $B)
echo $result  # Output: 8
```

### 1.2 Using `let`
`let` allows direct arithmetic evaluation. -->  No need for spaces between operators and numbers.
```bash
#!/bin/bash
a=5
b=3
let result=a+b
echo $result  # Output: 8
```

### 1.3 Using Double Parentheses `(( ))` (Recommended)
The `(( ))` syntax provides the cleanest way to perform arithmetic calculations in Bash.
```bash
#!/bin/bash
a=5
b=3
result=$((a + b))
echo $result  # Output: 8
```


- You may also programming language C stype manipulations of variables
``` bash 
echo $(( ++A ))
echo $(( --A ))
echo $(( A++ ))
echo $(( A-- ))
```
-  `((A++))` increments `A` after evaluation, whereas `((++A))` increments it before.
- `((A--))` decrements `A` after evaluation, whereas `((--A))` decrements it before.


### 1.4 Using `bc` (for Floating-Point Calculations)

- The `bc` command is used for floating-point calculations, as Bash does not support them natively.
- expr and "double parentheses" only return decimal output, they do not support floating values.
- For this we use another utility called **`bc`**, it referred to as **`Basic Calculator`**.
- It works in an interactive mode and also you can input to another command as well

```bash
#!/bin/bash
a=5
b=3
result=$(echo "scale=2; $a / $b" | bc)
echo $result  # Output: 1.66
```

## 2. Supported Arithmetic Operators
-  Addition  example:  `$((a + b))`   
-  Subtraction example: `$((a - b))`   
-  Multiplication example: `$((a * b))`   
-  Integer Division examlpe: `$((a / b))`  Performs **integer** division 
-  Floating-Point Division example: `echo "$a / $b" | bc -l`  Returns decimal result
-  Modulus example: `$((a % b))`  Returns remainder 
-  Exponentiation example: `$((a ** b))` Computes power 






