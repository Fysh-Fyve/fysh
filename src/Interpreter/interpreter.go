package interpreter

import (
	"fmt"
)

type FyshSpecies int

const (
	SpeciesFyshLiteral      FyshSpecies = iota // binary value
	SpeciesFyshBones                           // floating point value ><}-}-}>
	SpeciesFyshIdentifier                      // variable
	SpeciesHeartMultiply                       // <3 or ♡
	SpeciesHeartDivide                         // </3 or 💔
	SpeciesTadpoleLT                           // ~o (less than '<' )
	SpeciesTadpoleGT                           // o~ (greater than '>' )
	SpeciesTadpoleLTE                          // ~o≈ (less than equal to '<=' )
	SpeciesTadpoleGTE                          // o~≈ (greater than equal to '>=' )
	SpeciesAssign                              // ≈
	SpeciesEqual                               // ≈≈ (Equal to '==')
	SpeciesNotEqual                            // ~≈ (Not equal to '!=')
	SpeciesIncrement                           // >><fysh> (add 1 'fysh++')
	SpeciesDecrement                           // <fysh><< (sub 1 'fysh--')
	SpeciesFyshTankOpen                        // [ (used for Arrays, loops, and conditionals)
	SpeciesFyshTankClose                       // ]
	SpeciesFyshBowlOpen                        // ( (Used for FISHS (BEDMAS))
	SpeciesFyshBowlClose                       // )
	SpeciesFyshOpen                            // ><> (same as open curly bracket '{' )
	SpeciesFyshClose                           // <>< (same as closing curly bracket '}' )
	SpeciesWTFopen                             // WHAT THE FYSH (Throw error opening) ><!@#$>
	SpeciesWTFclose                            // WHAT THE FYSH (Throw error closing) <!@#$><
	SpeciesGrilledFysh                         // Random fysh ><###>
	SpeciesFyshLoop                            // ><(((@>
	SpeciesComment                             // ><//> Comment
	SpeciesMultilineComment                    // ></*> Comment <*/><
	SpeciesInvalid                             // Invalid token!
	SpeciesEnd                                 // End of the input
	SpeciesBitwiseAnd                          // &
	SpeciesBitwiseOr                           // |
	SpeciesCaret                               // ^
	SpeciesFyshWater                           // ~
	SpeciesShiftLeft                           // <<
	SpeciesShiftRight                          // >>
	SpeciesIf                                  // ><(((^>
	SpeciesElse                                // ><(((*>
	SpeciesFyshFood                            // -
	SpeciesAnchorLeft                          // (+o
	SpeciesAnchorRight                         // o+)
	SpeciesSubmarine                           // (submarine)<
	SpeciesSquid                               // <~ return operator
	SpeciesBrokenFysh                          // ><\/> or <\/>< (break)
)

// Token represents a token in the programming language, including its type and value.
type Token struct {
	Species    FyshSpecies
	Body       string
	intValue   uint32
	floatValue float64
}

func interpret(tokens []Token) {
	// Example variable store
	vars := make(map[string]float64)

	for _, token := range tokens {
		switch token.Species {
		case SpeciesFyshLiteral:
			fmt.Printf("Fysh Literal: %d\n", token.intValue)
		case SpeciesFyshBones: // Floating point value
			fmt.Printf("Fysh Bones: %f\n", token.floatValue)
		case SpeciesFyshIdentifier:
			fmt.Println("Fysh Identifier:", token.Body)
		default:
			fmt.Printf("Unhandled species: %v with value %s\n", token.Species, token.Body)
		}
	}

	fmt.Println("Variables:", vars)
}

func main() {
	tokens := []Token{
		{Species: SpeciesFyshIdentifier, Body: "x"},
	}
	interpret(tokens)
}
