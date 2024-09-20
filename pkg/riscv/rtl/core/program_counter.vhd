--! \file program_counter.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! The Program Counter.\n

--! It either increments itself by 4 or is set as the result of the ALU such as
--! when branching.
entity program_counter is
  generic (VERBOSE : boolean := false);
  port (
    pc_clk_i      : in std_ulogic := '0';  --! Program Counter Clock Signal.
    reset_i       : in std_ulogic := '0';  --! Reset Signal.
    pc_next_sel_i : in std_ulogic := '0';  --! Flag for selecting the next instruction.
    pc_alu_sel_i  : in std_ulogic := '1';  --! Flag to increment the value of PC with either an immediate value or 4.

    imm_x_i : in std_ulogic_vector (31 downto 0) := (others => '0');  -- PC increment immediate value.
    alu_i   : in std_ulogic_vector (31 downto 0) := (others => '0');  --! ALU Output. (use better name such as alu_out_i)

    pc_o            : out std_ulogic_vector (31 downto 0) := (others => '0');  --! Program Counter
    pc_alu_result_o : out std_ulogic_vector (31 downto 0) := (others => '0'));  --! Program Counter ALU Result.
end program_counter;

architecture rtl of program_counter is
  signal next_ins      : std_ulogic_vector(31 downto 0) := (others => '0');
  signal pc            : std_ulogic_vector(31 downto 0) := (others => '0');
  signal pc_alu        : std_ulogic_vector(31 downto 0) := (others => '0');
  signal pc_alu_result : std_ulogic_vector(31 downto 0) := (others => '0');
  signal pc_increment  : std_ulogic_vector(31 downto 0) := (others => '0');
begin
  pc_increment <= x"00000004";  -- hardwire program counter increment to 4

  with pc_next_sel_i select next_ins <=
    alu_i           when '1',
    pc_alu_result   when '0',
    (others => 'X') when others;

  with pc_alu_sel_i select pc_alu <=
    pc_increment    when '1',
    imm_x_i         when '0',
    (others => 'X') when others;


  pc_alu_result   <= std_ulogic_vector(unsigned(pc) + unsigned(pc_alu));
  pc_alu_result_o <= pc_alu_result;
  pc_o            <= pc;

  process(reset_i, pc_clk_i)
    use std.textio.all;
    variable l : line;
  begin
    if reset_i = '1' then
      pc <= (others => '0');
    elsif rising_edge(pc_clk_i) then
      if VERBOSE then
        report string'("next_ins: ") & to_hstring(next_ins);
      end if;
      pc <= next_ins;
    end if;
  end process;
end rtl;
