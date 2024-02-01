# Fysh Programming Language Compiler

Requires CMake and a C++ compiler.

## Testing

Run `make test` to run the unit tests.

## `></*>`

```c++
// the fysh's body represents the value of the fysh
//  ( = 0, { = 1


// single line comment
><//>

// block comments
></*>
<*/><

><fysh> ≈ ><{(({(o>    // assignment: fysh = b'10010' (normal equal signs should work too)
><fysh> ♡ ><{{({{(o>   // fysh * b'110110' (<3 can also be used instead of ♡)
><fysh> 💔 ><{{({{(o>  // fysh / b'110110' (</3 can also be used instead of 💔)
><fysh>   ><{{({{(o>   // fysh + b'110110'
><fysh>   <o}})}})><   // fysh - b'110110' (fysh direction represents its sign)
<fysh><                // -fysh (unary negative)
>><fysh> 		   // fysh++
<fysh><< 		   // fysh--


><fysh> o~ ><{((o>     // fysh > b'100'   (tadpole swims to the bigger fysh)
><fysh> ~o ><{((o>     // fysh < b'100'   (tadpole swims to the bigger fysh)
><fysh> ≈≈ ><{((o>     // fysh == b'100'  (normal equal signs should work too)
><fysh> ~≈ ><{((o>     // fysh != b'100'  (normal equal sign should work too)

// bit manipulation (subject to change in final version cuz this is feels uninspired)

><fysh> & ><{((o>        // fysh and b'101'
><fysh> | ><{((o>        // fysh or b'101'
><fysh> ^ ><{((o>        // fysh xor b'101'
^ ><fysh>                // bitwise not fysh
><fysh> << ><{((o>       // logical left shift
><fysh> >> ><{((o>       // logical right shift

><(((@> [ ><fysh> o~ ><{((o> ]  // while fysh > b'100' ([ ] are brackets)
><> 				     // open curly bracket
	<fysh><< 		     // fysh--
<>< 				     // closing curly  bracket


><(((^> // if
><>
 // code here
<><

><(((*> ><(((^>  // else if
><>
 // code here
<><

><(((*> // else
><>
 // code here
<><
><###>  // random 32 bit number

><!@#$> // Error code
This shouldn't happen. Error code
<!@#$><
```

```c++
// Factorial Example

><fysh>   ≈ ><{({o>    // b'101' (5 in binary)
><result> ≈ ><(({o>    // b'001' (1 in binary)

// While loop: Continue while fysh is greater than b'1' (1 in binary)
><(((@> [ ><fysh> o~ ><(({o> ]
><>    			         	// Opening curly bracket for while loop
	// Multiply result by fysh
	><result> ≈ ><result> ♡ ><fysh>

	// Decrement fysh
	<fysh><<
<><    		         	      // Closing curly bracket for while loop
```
