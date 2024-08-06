# 🐋 The Fyshhiker's Guide to the Ocean

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

## 🐙 Fyshing Manual

### 🐠 Chapter 1: Fysh Syntax
<details>
  <summary>Click to expand</summary>

#### 🐟 Variables
- Meet Steven, our fishy friend. In Fysh, variables like Steven are declared with `><name>`. Every line of fysh ends with a wave `~`.
```fysh
><Steven> ~
```

- Steven has binary scales. In Fysh, `}` represents `1` and `)` represents `0`. Here, Steven is valued at `0b101`, which is `5` in decimal.
```fysh
><steven> = ><})}> ~ 
```

- Steven doesn’t give a flying fysh about scale direction. `≈` for variable assignment is cool with them too.
```fysh
><steven> ≈ ><}({> ~
```

#### 👁️ Optional Visuals
- Steven is blind. You have the power to bless them with sight, but it's completely optional! You can make them biblically accurate by giving them multiple eyes.
```fysh
><steven> ≈ ><{({°> ~
><steven> ≈ ><{({o> ~
><steven> ≈ ><{({°°> ~
><steven> ≈ ><{({o°> ~
><steven> = ><{({°o°> ~
```

#### ➕ Arithmetic with Variables
- **Summing values:** A school of Fysh's value is the sum of each member. This gives Steven a value of `0b101 = 0b100 + 0b001 = ` (5 = 4 + 1).
```fysh
><steven> ≈ ><{((°> ><(({°> ~
```

- **Subtracting values:** Sometimes fysh are negative and start to swim backwards. This takes away from the school's value. Steven's value is `0b101 = 0b111 - 0b010 ` (5 = 7 - 2).
```fysh
><steven> ≈ ><{{{°> <°)})>< ~  # 0b101 = 0b111 - 0b010
```

- **Multiplying values:** Fysh often get lonely. This loneliness causes fysh to meet new fysh and proliferate. This gives Steven a value of `0b101010 = 0b110 * 0b111`. (42 = 6 * 7)
```fysh
><steven> = ><{{(°> <3 ><{{{°> ~
><steven> ≈ ><{{(°> ♡ ><{{{°> ~
```

- **Dividing values:** Not every fysh story is a happy one. At times, separation is inevitable, and their division breaks their heart. This gives Steven a value of `0b101 = 0b11001 / 0b101`. (5 = 25 / 5)
```fysh
><steven> ≈ ><{{(({°> </3 ><{({°> ~
><steven> ≈ ><{{(({°> 💔 ><{({°> ~
```

- **Using parentheses for complex operations:** Fysh are often abducted and isolated into fyshbowls `( )` for terrestrials' amusment. This makes the fysh sad and gives Steven a value of `0b101 = 0b101 / (0b101 - 0b100)`. (5 = 5 / (5 - 4))
```fysh
><steven> ≈ ><{({°> 💔 ( ><{({°> <°}))>< ) ~
```

#### 🔼🔽 Increment and Decrement
- **Increment:** As life goes on, we learn from our mistakes and improve. Steven’s self help journey allowed them to grow an extra tail, incrementing their value by 1.
```fysh
>><steven> ~
```

- **Decrement:** Sometimes we feel like a fyshup, a failure. And that's ok, it’s a part of being fysh. However for some fysh, this feeling is too much to handle and is internalized. They haven’t received the emotional support they need and have gone on a downward spiral, causing them to feel worthless. They begin to retreat and try to swim away in the opposite direction causing their value to decrement by 1.
```fysh
<steven><< ~
```

#### 🍢 Random Number Generation
**Random Number:** This is a grilled fysh. It generates a random signed 32-bit number that determines the
doneness of the fysh.
```fysh
><####> ~
```
</details>

### 📊 Chapter 2: Data Types

<details>
  <summary>Click to expand</summary>

#### 📏 Integers
- **Integer:** Steven is an integer represented using binary scales. They have scales that are either `1` or `0`. Steven's value is `0b101`, which is `5` in decimal.
```fysh
><steven> ≈ ><{({°> ~
```

#### 📐 Floating Point Numbers
- **Floats:** Steven can also be a float fysh. To seperate the integer and decimal parts, we use a fysh bone `-`. Steven's value is `5.5`.
```fysh
><steven> ≈ ><{({-{({°> ~
```
- **Floats with multiple bones:** Steven can also have multiple bones to seperate each decimal place. Steven's value is `5 + 0.2 + 0.05 = 5.25`.
```fysh
><steven> ≈ ><{({-{(-{({°> ~
```

- **Floats with numbers larger than 9:** If a value in the decimal place is greater than 9, it will occupy an extra decimal place. Steven's value is `15 + 0.15 + 0.005 15.155`.
```fysh
><steven> ≈ ><{{{{-{{{{-{({°> ~
```

#### 📝 Strings
- **Strings:** Steven can also be a string fysh. They speak using bubbles. Steven's value is `"Hello, World!"`.
```fysh
><steven> ≈ 🫧Hello, World!🫧 ~
```

#### 📦 Arrays and Traversal
- **Arrays:** A fysh tank `[ ]` is used create an array. Each item is separated by fysh food -.value is `[0b010, 0b010] = [2, 2]`.
```fysh
><steven> ≈ [><({(°> - ><({(°>] ~
```

- **Accessing Array Elements:** These fysh tanks can be traversed using a fysh tank `[ ]` with a number inside it. Steven returns the element at index 1. Array indexes start at 0.
```fysh
><steven>[><(({°>] ~
```
</details>

### 🧠 Chapter 3: Fysh Logic and Operations

<details>
  <summary>Click to expand</summary>

#### 🤔 Logical Operations
- **`AND (&&)`, `OR (||)`, and `NOT (!!)`**: 
  Steven is experiencing an existential crisis. They're questioning the very fabric of reality.
  - If steven is real `and` they found the truth, they're happy. (Steven && theTruth)
  - Steven is happy if either they're real `or` found the truth.  (Steven || theTruth)
  - But then Steven thought about it and said "hey it would be kinda cool if I wasn't real" and is now only happy if they're `not` real. (!!Steven)
```fysh
><steven> && ><TheTruth> ~
><steven> || ><TheTruth> ~
!! ><steven> ~
```

#### 🔧 Bitwise Operations
- Steven is bored and looking to have their bits rearranged. At Fysh, we're hereto help! We have provided Steven with a variety of tools and bitwise manipulations to satisfy their bit busting needs:
  - `AND (&)`
  - `OR (|)`
  - `XOR (^)`
  - `NOT (!)`
```fysh
><steven> & ><(({°> ~
><steven> | ><(({°> ~
><steven> ^ ><(({°> ~
! ><steven> ~
```
- **Logical shifts:** Steven can also use logical shifts! Steven shifts their bits to the left then right by 1.
  - **Left shift (`<<`):**
  - **Right shift (`>>`):**
```fysh
><steven> << ><(({°> ~
><steven> >> ><(({°> ~
```
#### 🐸 Tadpoles
Tadpoles are Fysh too. They swim towards bigger Fysh (they like the danger) and are represented by `~o` or `o~`. Here, we are checking if Steven is bigger than 5 and less than 7, respectively.

```fysh
><//> Greater/Less than
><steven> o~ ><{({°>
><steven> ~o ><{{{°>

><//> Greater/Less than or equal to (replace ~ with ≈ or =)
><steven> o= ><{({°>
><steven> ≈o ><{{{°>
```
</details>

### 🔄 Chapter 3: Control Structures
<details>
  <summary>Click to expand</summary>

#### 🔁 While Loops
- In the whirlpool of Fysh logic, the while loop, represented by `@` or `🌀`, with the condition stored in either `[ ]` or `( )`. Small fysh define the iterative heart `><>` and `<><`.

Here we repeat the loop while Steve is greater than 5. Steven decrements by 1 each iteration.
```fysh
🌀 [><steven> o~ ><{((°>]
><>
    <steven><< ~
<><

@ (><steven> o~ ><{((°>)
><>
    <steven><< ~
<><
```

#### ❓ Conditional Statements
Conditional statements run based on how each Fysh feels
- **`if` statement:** are happy since they're the condition you're looking for. They feel wanted and loved. They are represented by a happy Fysh

```fysh
><(((^> [><steven> o~ ><{((°>]
><>
    <steven><< ~
<><
```

- **`else` statement:** feel like they're the last resort, an afterthought. This makes them feel unimportant and sad. They are represented by a dead Fysh
```fysh
><(((*>
><>
    ><steven> ≈ ><(((°> ~
<><
```
- **`else if` statement:** are the middle child. They're not the first choice, but they're not the last either. They're represented by both a dead and happy Fysh
```fysh
><(((*> ><(((^> [><steven> ~o ><{((°>]
><>
    >><steven> ~
<><
```
</details>

### 🧑‍🔧 Chapter 4: Functions
<details>
  <summary>Click to expand</summary>

#### ✏️ Defining Functions
To define a function or SUBroutine, use a submarine `>(funcNameHere)` along with any parameters `><param>`. To return a value, use a squid `<~` or `🦑`. 

Here the function is called `submarine` and has 3 parameters. It returns the sum of the 3 parameters.
```fysh
>(submarine) ><param1> ><param2> ><param3>
><>
    <~ ><param1> ><param2> ><param3> ~ 
<><
```

#### 📞 Calling Functions
- To call a subroutine, put the submarine in a Fysh tank along with its arguments. If two or more params are next to each other, separate them with Fysh food `-`.
```fysh
[>(submarine) ><fysh1> - ><fysh2> - ><fysh3>] ~
```
</details>

### ⚓ Chapter 5: Output
<details>
  <summary>Click to expand</summary>

#### ⛓️ Output Value
When we finally reach our destination, we anchor ourselves. Anchors are used to output the value of a Fysh. They are represented by `(+o` or `⚓`

Here we're outputting `0b101` (5).
```fysh
(+o ><{({°> ~
```
</details>

### 💬 Chapter 6: Comments
<details>
  <summary>Click to expand</summary>

#### 🔉 Single-line Comments
Navigator Fysh are used to guide the reader through the code. They are represented by `><//>`.
```fysh
><//> What's cookin' good lookin'?
```

#### 🔊 Multi-line Comments
For longer explanations, multiline comments are used. They are represented by `></*>` and `<*\><`
```fysh
></*>
How to grill a Fysh:
1. Catch a Fysh
2. Grill the Fysh
3. Eat the Fysh
<*/><
```
</details>

### 📈 Examples
<details>
  <summary>Click to expand</summary>

#### ❗Factorial Example
This program calculates the factorial of number. In this case 5. The factorial of 5 is 120.
```fysh
><//> Factorial Example

><number>    ≈ ><{({°> ~ 
><factorial> ≈ ><(({°> ~

🌀 [><number> o~ ><(({°>]
><>
    ><factorial> ≈ ><factorial> ♡ ><number> ~
    <number><< ~
<><
(+o ><factorial> ~
```

Let's break it down:
1. `><number> ≈ ><{({°> ~` - Declare the number to calculate the factorial of. (5 in this case)
2. `><factorial> ≈ ><(({°> ~` - Declare the factorial variable. (1 in this case)
3. `🌀 [><number> o~ ><(({°>]` - While the number is greater than 1, do the following:
   1. `><factorial> ≈ ><factorial> ♡ ><number> ~` - Multiply the factorial by the number.
   2. `<number><< ~` - Decrement the number.
   3. Repeat until the number is 1.
4. `(+o ><factorial> ~` - Output the factorial.
</details>