package scanner_test

import (
	"testing"

	"github.com/Fysh-Fyve/fysh/src/scanner"
)

// go test -benchmem -run=^$ -bench "^BenchmarkIsRightTail.*$" github.com/Fysh-Fyve/fysh/src/scanner

func BenchmarkIsRightTailSlice(b *testing.B) {
	for i := 0; i < b.N; i++ {
		scanner.IsRightTailSlice('>')
		scanner.IsRightTailSlice('a')
		scanner.IsRightTailSlice('❳')
		scanner.IsRightTailSlice('x')
	}
}

func BenchmarkIsRightTailSwitch(b *testing.B) {
	for i := 0; i < b.N; i++ {
		scanner.IsRightTailSwitch('>')
		scanner.IsRightTailSlice('a')
		scanner.IsRightTailSwitch('❳')
		scanner.IsRightTailSwitch('x')
	}
}
