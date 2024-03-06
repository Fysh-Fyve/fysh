--! \file fysh_fyve_pkg.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A package containing shared stuff. Should probably be broken down.\n
package fysh_fyve is
  subtype dword_t is std_ulogic_vector (31 downto 0);
  -- Constants representing the ALU operations.
  subtype alu_op_t is std_ulogic_vector (2 downto 0);
  constant OP_ADD_SUB            : alu_op_t := "000";  --! A + B or A - B
  constant OP_SHIFT_LEFT         : alu_op_t := "001";  --! A << B(4:0)
  constant OP_LESS_THAN          : alu_op_t := "010";  --! A < B (signed)
  constant OP_LESS_THAN_UNSIGNED : alu_op_t := "011";  --! A < B (unsigned)
  constant OP_XOR                : alu_op_t := "100";  --! A ^ B
  constant OP_SHIFT_RIGHT        : alu_op_t := "101";  --! A >> B(4:0)
  constant OP_OR                 : alu_op_t := "110";  --! A | B
  constant OP_AND                : alu_op_t := "111";  --! A & B

  type mem_t is array (natural range <>) of dword_t;

  constant ROM_ADDR_W    : integer := 14;
  constant ROM_NUM_WORDS : integer := 2**ROM_ADDR_W;

  -- Constants representing the opcodes.
  subtype opcode_t is std_ulogic_vector (4 downto 0);
  constant OPCODE_LUI     : opcode_t := "01101";
  constant OPCODE_AUIPC   : opcode_t := "00101";
  --! Register-Immediate Operation
  constant OPCODE_REG_IM  : opcode_t := "00100";
  --! Register-Register Operation
  constant OPCODE_REG_REG : opcode_t := "01100";
  constant OPCODE_FENCE   : opcode_t := "00011";
  --! Those weird instructions that I'm not sure we're supporting in our
  --! execution environment
  -- csrrw, csrrs, csrrc
  -- csrrwi, csrrsi, csrrci
  -- ecall, ebreak
  -- uret, sret, mret
  -- wfi, sfence.vma
  constant OPCODE_ATOMIC  : opcode_t := "11100";
  constant OPCODE_LOAD    : opcode_t := "00000";
  constant OPCODE_STORE   : opcode_t := "01000";
  constant OPCODE_JAL     : opcode_t := "11011";
  constant OPCODE_JALR    : opcode_t := "11001";
  constant OPCODE_BRANCH  : opcode_t := "11000";

  -- Grilled fysh custom opcode
  constant OPCODE_FYSH : opcode_t := "11010";

  constant BEQ  : alu_op_t := "000";
  constant BNE  : alu_op_t := "001";
  constant BLT  : alu_op_t := "100";
  constant BGE  : alu_op_t := "101";
  constant BLTU : alu_op_t := "110";
  constant BGEU : alu_op_t := "111";

  constant DIV_NORMAL   : integer := 1;
  constant DIV_1_HZ     : integer := 62500000;
  constant DIV_10_HZ    : integer := 6250000;
  constant DIV_1_KHZ    : integer := 62500;
  constant DIV_62_5_MHZ : integer := 2;

  procedure write_opcode (l : inout std.textio.line; oc : in opcode_t);
  procedure write_func3 (l  : inout std.textio.line; f3 : in alu_op_t);
  procedure write_branch (l : inout std.textio.line; f3 : in alu_op_t);
end package fysh_fyve;

package body fysh_fyve is
  procedure write_func3 (l : inout std.textio.line; f3 : in alu_op_t) is
    use std.textio.all;
  begin
    case f3 is
      when OP_ADD_SUB            => write(l, string'("ADD"));
      when OP_SHIFT_LEFT         => write(l, string'(" SL"));
      when OP_LESS_THAN          => write(l, string'(" LT"));
      when OP_LESS_THAN_UNSIGNED => write(l, string'("LTU"));
      when OP_XOR                => write(l, string'("XOR"));
      when OP_SHIFT_RIGHT        => write(l, string'(" SR"));
      when OP_OR                 => write(l, string'(" OR"));
      when OP_AND                => write(l, string'("AND"));
      when others                => write(l, string'("ERR"));
    end case;
  end write_func3;

  procedure write_branch (l : inout std.textio.line; f3 : in alu_op_t) is
    use std.textio.all;
  begin
    case f3 is
      when BEQ    => write(l, string'("BEQ"));
      when BNE    => write(l, string'("BNE"));
      when BLT    => write(l, string'("BLT"));
      when BGE    => write(l, string'("BGE"));
      when BLTU   => write(l, string'("LTU"));
      when BGEU   => write(l, string'("GEU"));
      when others => write(l, string'("ERR"));
    end case;
  end write_branch;

  procedure write_opcode (l : inout std.textio.line; oc : in opcode_t) is
    use std.textio.all;
  begin
    case oc is
      when OPCODE_LUI     => write(l, string'("LUI   "));
      when OPCODE_AUIPC   => write(l, string'("AUIPC "));
      when OPCODE_REG_IM  => write(l, string'("REGIM "));
      when OPCODE_REG_REG => write(l, string'("REGREG"));
      when OPCODE_FENCE   => write(l, string'("FENCE "));
      when OPCODE_ATOMIC  => write(l, string'("ATOMIC"));
      when OPCODE_LOAD    => write(l, string'("LOAD  "));
      when OPCODE_STORE   => write(l, string'("STORE "));
      when OPCODE_JAL     => write(l, string'("JAL   "));
      when OPCODE_JALR    => write(l, string'("JALR  "));
      when OPCODE_BRANCH  => write(l, string'("BRANCH"));
      when OPCODE_FYSH    => write(l, string'("FYSH  "));
      when others         => write(l, string'("ERROR "));
    end case;
  end write_opcode;
end package body fysh_fyve;
