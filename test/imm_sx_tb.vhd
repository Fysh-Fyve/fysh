--! \file imm_sx_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
--! @endcond

--! Test bench for the Immediate Value Sign Extender.
entity imm_sx_tb is
end imm_sx_tb;

architecture test_bench of imm_sx_tb is
  signal instruction : std_ulogic_vector (31 downto 0);
  signal imm_val     : std_ulogic_vector (31 downto 0);

  procedure value_check(expected : std_ulogic_vector (31 downto 0)) is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 ns;
    if not (imm_val = expected) then
      --! Only on GHDL!
      -- write(my_line, string'("unexpected value, want = "));
      -- write(my_line, to_hstring(expected), left, 8);
      -- write(my_line, string'(", got = "));
      -- write(my_line, to_hstring(imm_val), left, 8);
      -- writeline(output, my_line);
      assert imm_val = expected;
    end if;
    wait for 1 ns;
  end procedure value_check;
begin
  imm_sx_inst : entity work.imm_sx(rtl) port map (
    instruction_i => instruction,
    imm_val_o     => imm_val);

  imm_test_cases : process
    variable rs1      : std_ulogic_vector(4 downto 0);
    variable rs2      : std_ulogic_vector(4 downto 0);
    variable rd       : std_ulogic_vector(4 downto 0);
    variable op       : std_ulogic_vector(6 downto 0);
    variable expected : std_ulogic_vector(31 downto 0);
  begin
    rs1         := "00001";
    rs2         := "00010";
    rd          := "00011";
    -- LUI, AUIPC
    op          := "0110111";
    instruction <= x"BEEFD" & rd & op;
    value_check(x"BEEFD000");

    -- ADDI (negative)
    op          := "0010011";
    instruction <= x"BAD" & rs1 & "000" & rd & op;
    value_check(x"FFFFFBAD");

    -- ADDI (positive)
    instruction <= x"0AD" & rs1 & "000" & rd & op;
    value_check(x"000000AD");

    -- SW
    op          := "0100011";
    instruction <= "0101010" & rs2 & rs1 & "010" & "10101" & op;
    value_check(x"00000555");

    -- JAL
    op          := "1101111";
    instruction <= '0' & x"55" & "01" &'1' & x"AA" & rd & op;
    value_check(x"000AAAAA");

    -- BEQ
    op          := "1100011";
    instruction <= '0' & "010101" & rs2 & rs1 & "000" & "0101" & '1' & op;
    value_check(x"00000AAA");

    stop;
  end process imm_test_cases;
end test_bench;
