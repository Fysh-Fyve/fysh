--! \file program_counter.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

entity program_counter is
  port (
    pc_clk_i, reset_i, pc_next_sel_i, pc_alu_sel_i : in std_ulogic;

    imm_x_i, alu_i : in  std_ulogic_vector (31 downto 0);
    pc_o, pc_alu_o : out std_ulogic_vector (31 downto 0));
end program_counter;

architecture Behavioral of program_counter is
  signal next_ins, pc_alu, pc_inc : std_ulogic_vector(31 downto 0);
begin
  pc_inc <= x"00000004";                -- hardwire pc_inc to 4
  with pc_next_sel_i select
    next_ins <= alu_i when '1', pc_alu_o when '0', (others => 'X') when others;
  with pc_alu_sel_i select
    pc_alu <= pc_inc when '1', imm_x_i when '0', (others => 'X') when others;
  pc_alu_o <= std_ulogic_vector(unsigned(pc_o) + unsigned(pc_alu));

  process(reset_i, pc_clk_i)
  begin
    if (reset_i = '0') then
      pc_o <= (others => '0');
    elsif rising_edge(pc_clk_i) then
      pc_o <= next_ins;
    end if;
  end process;
end Behavioral;
