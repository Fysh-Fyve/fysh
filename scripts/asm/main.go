package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
)

// 00000000: x"000037b7",  -- lui   x15, 0x3     // x15 = 0x00008000
// 00000004: x"12345117",  -- auipc  x2, 0x12345 // x2  = 0x00000004 + 0x12345000 = 0x12345004
// 00000008: x"00a10093",  -- addi   x1, x2, 10  // x1  = 0x12345004 + 0x0000000a = 0x1234500e
// 0000000c: x"4027da13",  -- srai  x20, x15, 2  // x20 = 0x00008000 >> 2 = 0x00002000
// 00000010: x"00f100b3",  -- add    x1, x2, x15 // x1  = 0x12345004 + 0x00008000 = 0x1234d004
// 00000014: x"402a00b3",  -- sub    x1, x20, x2 // x1  = 0x00002000 - 0x12345004 = 0xedcbcffc
// 00000018: x"0027a423",  -- sw     x2, 8(x15)  // m32(0x00003000 + 0x00000008) = 0x12345004
// 0000001c: x"0087a803",  -- lw    x16, 8(x15)  // x16 = sx(m32(0x00003000 + 0x00000008)) = 0x12345004
// 00000020: x"008000ef",  -- jal    x1, 0x28    // x1  = 0x00000024, pc = 0x00000020 + 0x00000008 = 0x00000028
// 00000024: x"00008013",  -- nop
// 00000028: x"03000267",  -- jalr   x4, 48(x0)  // x4  = 0x0000002c, pc = (0x00000030 + 0x00000000) & 0xfffffffe = 0x00000030
// 0000002c: x"00008013",  -- nop
// 00000030: x"02f00063",  -- beq  x0, x15, 0x50 // pc += (0x00000000 == 0x00008000 ? 0x00000020 : 4) = 0x00000034
// 00000034: x"03010063",  -- beq  x2, x16, 0x54 // pc += (0x12345004 == 0x12345004 ? 0x00000020 : 4) = 0x00000054

// x"00000013"

func writeMemory(w io.Writer) error {
	instructions := []uint32{
		0x00_00_87_b7,
		0x12_34_51_17,
		0x00_a1_00_93,
		0x40_27_da_13,
		0x00_f1_00_b3,
		0x40_2a_00_b3,
		0x00_27_a4_23,
		0x00_87_a8_03,
		0x00_80_00_ef,
		0x00_00_80_13,
		0x03_00_02_67,
		0x00_00_80_13,
		0x02_f0_00_63,
		0x03_01_00_63, // 34
		0x00_00_00_13, // 38
		0x00_00_00_13, // 3c
		0x00_00_00_13, // 40
		0x00_00_00_13, // 44
		0x00_00_00_13, // 48
		0x00_00_00_13, // 4c
		0x00_00_00_13, // 50
		0x00_00_00_13, // 54
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
