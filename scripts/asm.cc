/**
 * Jippitied from the original Go script.
 */
#include <cstdint>
#include <fstream>
#include <iostream>

// clang-format off
// 00000000: x"000107b7",  -- lui   x15, 0x10     // x15 = 0x00010000
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
// 00000054: x"00000063",  -- beq  x0, x0, 0x0   // pc += (0x00000000 == 0x00000000 ? 0x00000000 : 4) = 0x00000054
// clang-format on

// clang-format off
static const uint32_t instructions[] = {
  0x00'01'07'b7,
  0x12'34'51'17,
  0x00'a1'00'93,
  0x40'27'da'13,
  0x00'f1'00'b3,
  0x40'2a'00'b3,
  0x00'27'a4'23,
  0x00'87'a8'03,
  0x00'80'00'ef,
  0x00'00'80'13,
  0x03'00'02'67,
  0x00'00'80'13,
  0x02'f0'00'63,
  0x03'01'00'63, // 34
  0x00'00'00'13, // 38
  0x00'00'00'13, // 3c
  0x00'00'00'13, // 40
  0x00'00'00'13, // 44
  0x00'00'00'13, // 48
  0x00'00'00'13, // 4c
  0x00'00'00'13, // 50
  0x00'00'00'63, // 54
};
// clang-format on

void writeMemory(std::ostream &stream) {
  for (const auto &v : instructions) {
    uint32_t value = v;
    stream.write(reinterpret_cast<char *>(&value), sizeof(value));
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    writeMemory(std::cout);
  } else {
    std::ofstream outputFile(argv[1], std::ios::binary);
    if (!outputFile.is_open()) {
      std::cerr << "Error opening file for writing\n";
      return 1;
    }
    writeMemory(outputFile);
  }
  return 0;
}
