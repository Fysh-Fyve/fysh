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

  constant ROM_ADDR_W    : integer := 15;
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

  procedure write_opcode (l : inout std.textio.line; oc : in opcode_t);
end package fysh_fyve;

package body fysh_fyve is
  procedure write_opcode (l : inout std.textio.line; oc : in opcode_t) is
    use std.textio.all;
  begin
    case oc is
      when OPCODE_LUI     => write(l, string'("LUI"));
      when OPCODE_AUIPC   => write(l, string'("AUIPC"));
      when OPCODE_REG_IM  => write(l, string'("REG_IM"));
      when OPCODE_REG_REG => write(l, string'("REG_REG"));
      when OPCODE_FENCE   => write(l, string'("FENCE"));
      when OPCODE_ATOMIC  => write(l, string'("ATOMIC"));
      when OPCODE_LOAD    => write(l, string'("LOAD"));
      when OPCODE_STORE   => write(l, string'("STORE"));
      when OPCODE_JAL     => write(l, string'("JAL"));
      when OPCODE_JALR    => write(l, string'("JALR"));
      when OPCODE_BRANCH  => write(l, string'("BRANCH"));
      when others         => write(l, string'("INVALID"));
    end case;
  end write_opcode;
end package body fysh_fyve;
