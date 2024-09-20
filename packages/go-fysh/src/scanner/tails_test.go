package scanner_test

import (
	"testing"

	"github.com/Fysh-Fyve/fysh/src/scanner"
)

// go test -benchmem -run=^$ -bench "^BenchmarkIsRightTail.*$" github.com/Fysh-Fyve/fysh/src/scanner

func BenchmarkIsRightTailSlice(b *testing.B) {
	for i := 0; i < b.N; i++ {
		IsLeftTailSlice('>')
		IsLeftTailSlice('a')
		IsLeftTailSlice('❳')
		IsLeftTailSlice('x')
	}
}

func BenchmarkIsRightTailSwitch(b *testing.B) {
	for i := 0; i < b.N; i++ {
		scanner.IsLeftTailSwitch('>')
		scanner.IsLeftTailSwitch('a')
		scanner.IsLeftTailSwitch('❳')
		scanner.IsLeftTailSwitch('x')
	}
}

// we simply incorporate the logic in the actual switch statements
// so no need for these functions

// func IsRightTailSlice(ch rune) bool {
// 	rightTails := []rune{'>', '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵'}
// 	for _, tale := range rightTails {
// 		if ch == tale {
// 			return true
// 		}
// 	}
// 	return false
// }
//
// func IsRightTailSwitch(ch rune) bool {
// 	switch ch {
// 	case '>', '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵':
// 		return true
// 	default:
// 		return false
// 	}
// }

func IsLeftTailSlice(ch rune) bool {
	leftTails := []rune{'<', '⧼', '⟨', '⟪', '〈', '⦃', '⦅', '⦇', '⦉', '⦋', '⦍', '⦏', '⦑', '⦓', '⦕', '〈', '❬', '❮', '❰', '❲', '❴'}
	for _, tale := range leftTails {
		if ch == tale {
			return true
		}
	}
	return false
}
