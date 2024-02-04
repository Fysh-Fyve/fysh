package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
)

// x"000087b7",  -- lui   x15, 0x8     // x15 = 0x00008000
// x"12345117",  -- auipc  x2, 0x12345 // x2  = 0x00000004 + 0x12345000 = 0x12345004
// x"00a10093",  -- addi   x1, x2, 10  // x1  = 0x12345004 + 0x0000000a = 0x1234500e
// x"4027da13",  -- srai  x20, x15, 2  // x20 = 0x00008000 >> 2 = 0x00002000
// x"00f100b3",  -- add    x1, x2, x15 // x1  = 0x12345004 + 0x00008000 = 0x1234d004
// x"402a00b3",  -- sub    x1, x20, x2 // x1  = 0x00002000 - 0x12345004 = 0xedcbcffc

func writeMemory(w io.Writer) error {
	instructions := []uint32{
		0x00_00_87_b7,
		0x12_34_51_17,
		0x00_a1_00_93,
		0x40_27_da_13,
		0x00_f1_00_b3,
		0x40_2a_00_b3,
	}
	out := make([]byte, 0, len(instructions)*4)
	for _, v := range instructions {
		out = binary.LittleEndian.AppendUint32(out, v)
	}

	_, err := w.Write(out)
	return err
}

func run() error {
	if len(os.Args) < 2 {
		return writeMemory(os.Stdout)
	}

	f, err := os.Create(os.Args[1])
	if err != nil {
		return err
	}
	defer f.Close()

	return writeMemory(f)
}

func main() {
	if err := run(); err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}
}
