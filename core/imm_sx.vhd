--! \file imm_sx.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Immediate Value Sign-extender.\n

--! Takes an immediate value from an instruction and outputs its sign-extended
--! value.
entity imm_sx is
  port (
    instruction_i : in  std_ulogic_vector (31 downto 0);  --! The 32-bit instruction.
    imm_val_o     : out std_ulogic_vector (31 downto 0));  --! The immediate value, sign-extended.
end imm_sx;

architecture rtl of imm_sx is
  --! Take 20 bits from the instruction and output as the high 20 bits.
  --! The lower 12 bits are zeroed.\n
  --! ins[31:12] (20 bits) & (12:0 => 0)
  signal imm_hi_20  : std_ulogic_vector (31 downto 0);
  --! Take 12 bits from the instruction and sign extend as the low 12 bits.\n
  --! sext ins[31:20] (12 bits)
  signal imm_lo_12  : std_ulogic_vector (31 downto 0);
  --! Take 12 bits from the instruction (mixed) and sign extend as the low 12
  --! bits (for store instructions).\n
  --! sext ins[31:25] (7 bits) & ins[11:7] (5 bits)
  signal imm_st_12  : std_ulogic_vector (31 downto 0);
  --! Take 12 bits from the instruction (mixed) and sign extend as the low 12
  --! bits shifted left by 1, the LSb is zeroed (for branch instructions).\n
  --! sext ins[31] & ins[7] & ins[30:25] (6 bits) & ins[11:8] (4 bits) & 0
  signal imm_br_12  : std_ulogic_vector (31 downto 0);
  --! Take 20 bits from the instruction (mixed) and sign extend as the low 20
  --! bits shifted left by 1, the LSb is zeroed (unique to JAL).\n
  --! sext ins[31] & ins[19:12] (8 bits) & ins[20] & ins[30:21] (10 bits) & 0
  signal imm_jal_20 : std_ulogic_vector (31 downto 0);
begin
  with instruction_i(6 downto 2) select imm_val_o <=
    imm_hi_20       when "00101" |"01101",             -- lui, auipc
    imm_lo_12       when "00000" | "00100" | "11001",  -- alu(imm), loads, jalr
    imm_st_12       when "01000",                      -- stores
    imm_br_12       when "11000",                      -- branches
    imm_jal_20      when "11011",                      -- jal
    (others => 'X') when others;

  imm_hi_20 <= instruction_i(31 downto 12) & (11 downto 0 => '0');

  imm_lo_12 <=
    (31 downto 12 => instruction_i(31))  -- Sign extend
    & instruction_i(31 downto 20);       -- 11:0

  imm_st_12 <=
    (31 downto 12 => instruction_i(31))  -- Sign extend
    & instruction_i(31 downto 25)        -- 11:5
    & instruction_i(11 downto 7);        -- 4:0

  imm_jal_20 <=
    (31 downto 21 => instruction_i(31))  -- Sign extend
    & instruction_i(31)                  -- 20
    & instruction_i(19 downto 12)        -- 19:12
    & instruction_i(20)                  -- 11
    & instruction_i(30 downto 21)        -- 10:1
    & '0';                               -- 9:0

  imm_br_12 <=
    (31 downto 13 => instruction_i(31))  -- Sign extend
    & instruction_i(31)                  -- 12
    & instruction_i(7)                   -- 11
    & instruction_i(30 downto 25)        -- 10:5
    & instruction_i(11 downto 8)         -- 4:1
    & '0';
end rtl;
