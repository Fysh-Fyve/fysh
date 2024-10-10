# 🌊 The Fyshhiker's Guide to the Ocean 🐋 


## Introduction

**Fysh** is an esoteric programming language that embraces creativity and a playful theme. It uses fish-related symbols and terms to represent programming concepts. This guide aims to provide a clear understanding of Fysh's syntax and features while maintaining its fun and engaging spirit.

---

## 👩‍💻 How to Compile and Run Fysh

### ⚙️ Option 1: Using Our Online Interpreter
1. **Visit Our Webpage**
   - Visit our webpage at: https://fysh-fyve.github.io/

2. **Press Play**
   - Write your code and press the play button


### ⚙️ Option 2: Using VSCode

1. **Download the Fysh VSCode Extension**
   - Install the Fysh extension from the VSCode marketplace.

2. **Create a `.fysh` File**
   - Open VSCode and create a new file with the extension `.fysh`.

3. **Write Your Code**
   - Start coding in Fysh!

4. **Run Your Code**
   - Press the run button provided by the extension to execute your program.


### ⚙️ Option 3: Using Command Line
1. **Install the Latest Version of Fysh**
   - Use the Go command to install Fysh:

     ```bash
     go install github.com/Fysh-Fyve/fysh/pkg/go-fysh@latest
     ```

2. **Execute Your Fysh Program**
   - Run your program using the generated Fysh interpreter:

     ```bash
     fysh <filename>.fysh
     ```

---
## 🐙 Fyshing Manual

### 💬 Chapter 1: Comments

<details>
  <summary>Click to expand</summary>

#### 🔉 Single-line Comments

Single-line comments start with navigator fish `><//>`.

```fysh
><//> What's cookin' good lookin'?
```

#### 🔊 Multi-line Comments

For longer explanations, multiline comments are used. They are enclosed with
`></*>` and `<*\><`

```fysh
></*>
How to grill a Fysh:
1. Catch a Fysh
2. Grill the Fysh
3. Eat the Fysh
<*/><
```

</details>


### 🐠 Chapter 2: Fysh Syntax

<details>
  <summary>Click to expand</summary>

#### 🐟 Variables

In Fysh, variables are declared using the syntax `><variableName>`. Every line of Fysh code ends with a tilde `~`.

**Example:**
```fysh
><Steven> ~
```

#### 👉🏻 Assigning Values
Variables can be assigned values using either the `≈` or `=` operator.

**Example:**
`Steven` is assigned the value of `CoolFysh`:
```fysh
><Steven> ≈ ><CoolFysh> ~
```

#### 🔟 Binary Scales

A fysh's scales represents it's binary value `><})}>`:

- **Scales Representing Binary 1:** `{` and `}`
- **Scales Representing Binary 0:** `(` and `)`

> **Note:** The direction of the scales does not matter. `{` and `}` both represent binary `1`, and `(` and `)` both represent binary `0`.

**Example:**

Here we assign the binary value `0b101` (5 in decimal) to `Steven`:

```fysh
><steven> ≈ ><})}> ~ 
```

#### 👁️ Optional Visuals

`><})}>` is blind, but we can give it eyes... multiple eyes! 🐟👀
**Valid Eye Symbols:** `o`, `°`
> **Note:** This is completely optional. 

```fysh
><steven> ≈ ><})}°>   ~
><steven> ≈ ><{({°>   ~
><steven> ≈ ><{({o>   ~ 
><steven> ≈ ><{({°°>  ~
><steven> ≈ ><{({o°>  ~
><steven> ≈ ><}({°o°> ~
```
</details>

### ➕ Chapter 3: Arithmetics
<details>
  <summary>Click to expand</summary>
#### Addition
To add two fyshes, place variables or values next to each other. The value of a school of Fysh is the sum of each member. 

**Example:**
steven = 4 + 1 (binary: `0b100` + `0b001`)
```fysh
><steven> ≈ ><{((°> ><(({°> ~
```
In this example:

- `><{((°>` represents `0b100` (4)
- `><(({°>` represents `0b001` (1)
- `steven` is assigned `4 + 1 = 5`

#### ➖ Subtraction
Some fysh are negative and start to swim away. Fysh swimming to the left take away from the school's value.
> **Note:** Fysh swim to the left flips the sign of the fysh. So a negative variable swimming left will become positive.

**Example:**
steven = 7 - 2 (binary: `0b111` - `0b010`)
```fysh
><steven> ≈ ><{{{°> <°)})>< ~ 
```
#### ❤️ Multiplication
Fysh often get lonely. This loneliness causes fysh to meet new fysh and proliferate, quickly multiplying their numbers.
> **Note:** Every possible representation of a heart is valid for multiplication. If there's a heart that doesn't work, please let us know.

**Example:**
steven = 6 * 7 (binary: `0b110` * `0b111`)
```fysh
><steven> = ><{{(°> <3 ><{{{°> ~
><steven> ≈ ><{{(°> ♡ ><{{{°> ~
><steven> ≈ ><{{(°> 💘 ><{{{°> ~
```

#### 💔 Division
Not every fysh story is a happy one. At times, separation is inevitable, and their division breaks their hearts, causing their numbers to dwindle.
Division is represented by a broken heart `</3` or `💔`.

**Example:**
Steven = 25 / 5 (binary: `0b11001` / `0b101`)
```fysh
><steven> ≈ ><{{(({°> </3 ><{({°> ~
><steven> ≈ ><{{(({°> 💔 ><{({°> ~
```

#### 🎣 Fysh Bowls (Parentheses)

Fysh are often abducted and kept in small glass fysh bowls for the amusement of land-dwellers. These bowls are represented by `( )`.
This is used to group fysh together, allowing their operations to be performed first.

**Example:**
steven = 5 / (5 - 4) (binary: `0b101` / (`0b101` - `0b100`))
```fysh
><steven> ≈ ><{({°> 💔 ( ><{({°> <°}))>< ) ~
```


#### 📈 Increment
  As life goes on, we learn from our mistakes and improve.
  Steven’s self help journey allowed them to grow an extra tail, incrementing
  their value by 1.

**Example:**
steven = steven + 1
```fysh
>><steven> ~
```

#### 📉 Decrement
  Sometimes we feel like a fyshup, a failure. And that's ok, it’s
  a part of being fysh. However for some fysh, this feeling is too much to
  handle and is internalized. They haven’t received the emotional support they
  need and have gone on a downward spiral, causing them to feel worthless. They
  begin to retreat and try to swim away in the opposite direction causing their
  value to decrement by 1.

**Example:**
steven = steven - 1
```fysh
<steven><< ~
```

#### 🍢 Random Number Generation
The random number generator is represented with a grilled fysh. It generates a random signed 32-bit number that determines the doneness of the fysh.

**Example:**
```fysh
><####> ~
```

</details>

### ⚓ Chapter 5: Output

<details>
  <summary>Click to expand</summary>

#### ⛓️ Output Value

To output the value of a variable, use an anchor `(+o` or `⚓`.



**Example:**
Output the value of `Steven`:
```fysh
(+o ><{({°> ~
```

</details>


### 📊 Chapter 4: Data Types

<details>
  <summary>Click to expand</summary>

#### 📏 Integers
  Fysh with binary scales `><})}>` are integers.

**Example:**
Steven = 5 (binary: `0b101`)
```fysh
><steven> ≈ ><{({°> ~
```

#### 🦴 Floats with One Bone
  Some people like to play with their food, so they pick away at steven, leaving only a fraction of them behind. This exposes the bones (`-`) of the fysh. Bones help to separate the integer and decimal parts of the fysh.

**Example:**
```fysh
><steven> ≈ ><{{{-{({°> ~
```
Explanation:

- `><{{{-` represents the integer part `7` (binary: `0b111`)
- `-{({°>` represents the fractional part `0.5` (binary: `0b101`)
- Steven's value is `7 + 0.5 = 7.5`.

#### 🦴🦴🦴 Floats with Multiple Bones
When multiple bones are present, the additonal values are added at the end of the decimal part. Steven's value is `2 + 0.15 + 0.005 = 15.155`.

**Example:**
```fysh
><steven> ≈ ><{(-{{{{-{{{°> ~
```
Explanation:

- `><{(-` represents the integer part `2` (binary: `0b10`)
- `-{{{{-` represents the fractional part `0.15` (binary: `0b1111`)
- `-{{{°>` represents the additional fractional part `0.007` (binary: `0b111`)
- steven's value is `2 + 0.15 + 0.007 = 2.157`.

#### 🫧 Bubbles (Strings)
Fysh blow bubbles, and these bubbles can be used to represent strings. 
Bubble strings are enclosed in `🫧` or `*`.

**Example:**
```fysh
><steven> ≈ 🫧Hello, World!🫧 ~
><steven> = *Hello, World!* ~
```

#### 📦 Arrays and Traversal
Arrays are represented by a fysh tank `[ ]`. Each item is separated
  by fysh food `-`.

**Example:**
steven = [6,2] (binary: `[0b110, 0b010]`)
```fysh
><steven> ≈ [><{{(°> - ><({(°>] ~
```

  To access array elements, use the array variable followed by `[index]`.
> **Note:** Array indexes start at 0.

**Example:**
steven[1] (accessing the second element of steven)
```fysh
><steven>[><(({°>] ~
```
</details>

### 🧠 Chapter 6: Fysh Logic and Operations

<details>
  <summary>Click to expand</summary>

#### 🐸 Tadpoles

The greater than and less than operations are represented by tadpoles `~o` and `o~`. Tadpoles swim towards the bigger Fysh, indicating the direction of the comparison.

**Example:**
```fysh
><//> Greater/Less than
><steven> o~ ><{({°> ~    ><//> Steven > 1
><steven> ~o ><{{{°> ~    ><//> Steven < 7

><//> Greater/Less than or equal to (replace ~ with ≈ or =)
><steven> o≈ ><{({°> ~    ><//> Steven >= 1
><steven> =o ><{{{°> ~    ><//> Steven <= 7
```

#### 🤔 Logical Operations

Fysh supports standard logical operations:

- **AND**: `&&`
- **OR**: `||`
- **NOT**: `!!`

**Example:**
```fysh
><steven> && ><Alive> ~   ><//> Steven and Alive
><steven> || ><Alive> ~   ><//> Steven or Alive
!! ><steven> ~            ><//> Not Steven
```

#### 🔧 Bitwise Operations

  Steven is bored and looking to have their bits rearranged. At Fysh, we're
  here to help! Steven has been provided with a variety of tools and bitwise
  manipulations to satisfy their bit busting needs:
  - `AND (&)`
  - `OR (|)`
  - `XOR (^)`
  - `NOT (!)`
  
> **Note:** Currently does not support floats

```fysh
><steven> & ><(({°> ~  ><//> Steven and 1
><steven> | ><(({°> ~  ><//> Steven or 1
><steven> ^ ><(({°> ~  ><//> Steven xor 1
! ><steven> ~          ><//> Not Steven
```
#### 🔄 Logical Shift Operations
 You can even use logical shifts! Steven shifts their
  bits to the left then right by 1.
  - **Left shift (`<<`):**
  - **Right shift (`>>`):**


> **Note:** Currently does not support floats

**Example:**
```fysh
><steven> << ><(({°> ~   ><//> Steven left shift 1
><steven> >> ><(({°> ~   ><//> Steven right shift 1
```
</details>

### 🔄 Chapter 7: Control Structures

<details>
  <summary>Click to expand</summary>

#### 🔁 While Loops

  While loops can be represented using whirlpools:

- `@`
- `🌀`
- `><(((@>`

The condition stored in either:
- `( )` fysh bowl
- `[ ]` fysh tank

The loop body is enclosed between `><>` and `<><`.

**Example:**
```fysh
🌀 [><steven> o~ ><{((°>]            ><//> while steven > 4
><>
    <steven><< ~                    ><//> steven--
<><

@ (><steven> ~o ><{((°>)            ><//> while steven < 4
><>
    >><steven> ~                    ><//> steven++
<><

><(((@> [><steven> o≈ ><{((°>]      ><//> while steven >= 4
><>
    <steven><< ~                    ><//> steven--
<><
```

#### ❓ Conditional Statements

Conditional statements run based on how each Fysh feels

##### 😊 **`if` Statements: The Happy Fysh `><(((^>`**
These Fysh are overjoyed because they're the center of attention—they feel wanted and loved.

**Example:**
```fysh
><(((^> [><steven> o~ ><{((°>]     ><//> if steven > 4
><>
    <steven><< ~                   ><//> steven--
<><
```

##### 😵 **`else` Statement: The Sad (Dead) Fysh `><(((*>`** 
These fysh feel like they're an afterthought and are often left behind. This makes them feel sad and dead inside.

**Example:**
```fysh
><(((*>                      ><//> else
><>
    ><steven> ≈ ><(((°> ~    ><//> steven = 0
<><
```

##### 😐 **`else if` Statement: The Middle Child `><(((*> ><(((^>`**
These fysh are a combination of a dead and a happy fish, symbolizing the middle child. Not the first choice but not the last.

```fysh
><(((*> ><(((^> [><steven> ~o ><{((°>]     ><//> else if steven < 4
><>
    >><steven> ~                           ><//> steven++
<><
```

</details>

### 🧑‍🔧 Chapter 8: Functions

<details>
  <summary>Click to expand</summary>

#### ✏️ Defining Functions


Functions (subroutines) are defined using a submarine `>(functionName)`, with parameters `><param>`. The function body is enclosed between `><>` and `<><`. To return a value, use a squid `<~` or `🦑`.

**Example:**
```fysh
>(add) ><param1> ><param2>       ><//> def add(param1, param2)
><>
    <~ ><param1> ♡ ><param2> ~  ><//> Return the product of param1 and param2
<><
```

#### 📞 Calling Functions

To call a function, place the submarine in a fish tank `[ ]`, along with its arguments, separated by fish food `-`.

> **Note:** The submarine can be placed anywhere in the fish tank as long as the arguments are in the correct order.

**Example:**
```fysh
[>(submarine) ><fysh1> - ><fysh2>] ~     ><//> submarine(fysh1, fysh2)
```

</details>



### 📈 Examples

<details>
  <summary>Click to expand</summary>

<details>
  <summary>❗Factorial Example</summary>

#### ❗Factorial Example

This program calculates the factorial of a number, in this case, 5. The factorial of 5 is 120.

```fysh
><//> Factorial Example

><number>    ≈ ><{({°> ~                        ><//> number = 5
><factorial> ≈ ><(({°> ~                        ><//> factorial = 1

🌀 [><number> o~ ><(({°>]
><>
    ><factorial> ≈ ><factorial> ♡ ><number> ~   ><//> factorial = factorial * number
    <number><< ~                                ><//> number--
<><

⚓ ><factorial> ~                               ><//> print(factorial)
```

**Explanation:**

1. **Variable Declarations:**
   - `><number> ≈ ><{({°> ~` assigns 5 to `number`.
   - `><factorial> ≈ ><(({°> ~` assigns 1 to `factorial`.

2. **While Loop:**
   - `🌀 [><number> o~ ><(({°>]` loops while `number` > 1.
   - Inside the loop:
     - Multiply `factorial` by `number`.
     - Decrement `number`.

3. **Output:**
   - `⚓ ><factorial> ~` outputs the calculated factorial.

</details>

<details>
  <summary>🔁Fibonacci Example (recursion)</summary>
  
#### 🔁Fibonacci Example

This program calculates the nth Fibonacci number, in this case, the 7th. The 7th Fibonacci number is equal to 13.

```fysh
><//> Fibonacci Example

>(fib) ><n>                            ><//> def fib(n)
><>
    ><(((^> [><n> ~o ><({(°>]          ><//> if n < 2
    ><>
        🦑 ><n> ~                      ><//> Return 'n' if 'n' < 2
    <><
    ><(((*>                            ><//> else
    ><>
        ><a> ≈ [>(fib) ><n> <({><] ~   ><//> a = fib(n - 1)
        ><b> ≈ [>(fib) ><n> <{(><] ~   ><//> b = fib(n - 2)
        🦑 ><a> ><b> ~                 ><//> Return a + b
    <><
<><

><result> ≈ [>(fib) ><{{{°>] ~         ><//> result = fib(7)
⚓ ><result> ~                         ><//> print(result)
```

**Explanation:**

1. **Function Definition:**
   - `>(fib) ><n>` defines the function `fib` with parameter `n`.
   - If `n` is less than 2:
     - Return `n`.
   - Else:
     - Compute `a = fib(n - 1)`.
     - Compute `b = fib(n - 2)`.
     - Return `a + b`.

2. **Function Call:**
   - `><result> ≈ [>(fib) ><{{{°>] ~` calls `fib(7)` and assigns the result to `result`. result = fib(7)

3. **Output:**
   - `⚓ ><result> ~` outputs the 7th Fibonacci number (13).
</details>
</details>

---

This concludes the **Fyshhiker's Guide to the Ocean**. Happy Fyshing!
