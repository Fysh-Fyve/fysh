# 🐠 Fysh Language Guide

## 🤔 Why is it called Fysh? 

Because "fish" was already taken ([Fish](https://esolangs.org/wiki/Fish)).

## 👩‍💻 How to Compile and Run Fysh


### ⚙️ Option 1: Using VSCode
1. Download the `Fysh` VSCode extension.
2. Create a `.fysh` file.
3. Write your code.
4. Press the run button.

### ⚙️ Option 2: Using Command Line
1. Clone the repository.
2. Run `go build`.
3. Execute with `./fysh <filename>.fysh`.

## 🐠 Fysh Syntax
<details>
  <summary>Click to expand</summary>

### 📜 General Syntax
- All lines must end with `~` (similar to `;` in other languages).

### 🐟 Variables
- Variables are represented as fish with a name inside them.
```fysh
><steven> ~
```
- Binary values are defined using `}` for 1 and `)` for 0.
```fysh
><steven> = ><})}> ~  # 0b101 (5 in decimal)
```
- Assignment can also use `≈`:
```fysh
><steven> ≈ ><}({> ~
```

### 👁️ Optional Visuals
- Variables can have optional eyes.
```fysh
><steven> ≈ ><{({°> ~
```

### ➕ Arithmetic with Variables
- Summing values:
```fysh
><steven> ≈ ><{((°> ><(({°> ~  # 0b101 = 0b100 + 0b001
```
- Subtracting values: (Fish swimming left makes it negative of whatever value is inside)
```fysh
><steven> ≈ ><{{{°> <°)})>< ~  # 0b101 = 0b111 - 0b010
```
- Multiplying values:
```fysh
><steven> ≈ ><{{(°> ♡ ><{{{°> ~  # 0b101010 = 0b110 * 0b111
```
- Dividing values:
```fysh
><steven> ≈ ><{{(({°> 💔 ><{({°> ~  # 0b101 = 0b11001 / 0b101
```
- Using parentheses for complex operations:
```fysh
><steven> ≈ ><{({°> 💔 ( ><{({°> <°}))>< ) ~
```

### 🔼🔽 Increment and Decrement
- Increment:
```fysh
>><steven> ~
```
- Decrement:
```fysh
<steven><< ~
```

### 🤔 Logical Operations
- Logical operations using `&&`, `||`, and `!`:
```fysh
><steven> && ><fysh> ~
><steven> || ><fysh> ~
!! ><steven> ~
```

### 🔧 Bitwise Operations
- `AND (&)`, `OR (|)`, `XOR (^)`, and `NOT (!)`:
```fysh
><steven> & ><(({°> ~
><steven> | ><(({°> ~
><steven> ^ ><(({°> ~
! ><steven> ~
```
- Logical shifts:
```fysh
><steven> << ><(({°> ~
><steven> >> ><(({°> ~
```
</details>

## 🔄 Control Structures
<details>
  <summary>Click to expand</summary>

### 🔁 While Loops
- Represented by `@`, `🌀`,`><@>` or `><(((@>` with conditions in `[ ]` or `()`:
```fysh
><(((@> [><steven> o~ ><{((°>]
><>
    <steven><< ~
<><
```

### ❓ Conditional Statements
- `if` statement:
```fysh
><(((^> [><steven> o~ ><{((°>]
><>
    <steven><< ~
<><
```
- `else if` statement:
```fysh
><(((*> ><(((^> [><steven> ~o ><{((°>]
><>
    >><steven> ~
<><
```
- `else` statement:
```fysh
><(((*>
><>
    ><steven> ≈ ><(((°> ~
<><
```
</details>

## 🧑‍🔧 Functions
<details>
  <summary>Click to expand</summary>

### ✏️ Defining Functions
- Functions (SUBroutines) are defined with a submarine `>(funcNameHere)` and parameters `><param>`:
```fysh
>(submarine) ><param1> ><param2> ><param3>
><>
    <~ <fysh>< ~  # Explicit return
<><
```

### 📞 Calling Functions
- Call a function using a fysh tank `[]` with its arguments. Each argument is seperated by fysh food `-`:
```fysh
[>(submarine) ><fysh1> - ><fysh2> - ><fysh3>] ~
```
</details>

## ⚓ Output
<details>
  <summary>Click to expand</summary>

- Use `(+o` or `⚓` to print the value of a fysh:
```fysh
(+o ><{({°> ~  # Prints 5
```
</details>

## 💬 Comments
<details>
  <summary>Click to expand</summary>

### Single-line Comments
- Represented by `><//>`:
```fysh
><//> This is a comment
```

### Multi-line Comments
- Represented by `></*>` and `<*/><`:
```fysh
></*>
Multi-line comment
<*/><
```
</details>

## 📈 Example: Factorial Calculation
<details>
  <summary>Click to expand</summary>

```fysh
><//> Factorial Example

><number>    ≈ ><{({°> ~  ><//> b101 = 5
><factorial> ≈ ><(({°> ~  ><//> b001 = 1

><//> while number > 1
><(((@> [><number> o~ ><(({°>]
><>
    ><//> factorial = factorial * number
    ><factorial> ≈ ><factorial> ♡ ><number> ~

    ><//> number -= 1
    <number><< ~
<><

(+o ><factorial> ~
```
</details>