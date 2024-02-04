package main

import (
	"encoding/hex"
	"errors"
	"fmt"
	"io"
	"os"
)

const INDENT = 4

func readMemory(r io.Reader) error {
	h := make([]byte, 4)

	for {
		if _, err := r.Read(h); err != nil {
			// Actual error
			if !errors.Is(err, io.EOF) {
				return err
			}
			// EOF
			break
		}

		fmt.Printf("%*s", INDENT, "")
		fmt.Printf("x\"%s\",\n", hex.EncodeToString(h))
	}
	return nil
}

func run() error {
	if len(os.Args) < 2 {
		return readMemory(os.Stdin)
	}

	f, err := os.Open(os.Args[1])
	if err != nil {
		return err
	}
	defer f.Close()

	return readMemory(f)
}

func main() {
	if err := run(); err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}
}
