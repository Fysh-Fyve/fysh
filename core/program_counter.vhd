library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity program_counter is
  port (
    pc_clk, reset, pc_next_sel, pc_alu_sel : in std_ulogic;

    imm_x, alu : in  std_ulogic_vector (31 downto 0);
    pc, pc_alu : out std_ulogic_vector (31 downto 0));
end program_counter;

architecture Behavioral of program_counter is
  signal next_ins, pc_alu_in, pc_inc : std_ulogic_vector(31 downto 0);
begin
  pc_inc <= x"00000004";                -- hardwire pc_inc to 4
  with pc_next_sel select
    next_ins <= alu when '1', pc_alu when '0', (others => 'X') when others;
  with pc_alu_sel select
    pc_alu_in <= pc_inc when '1', imm_x when '0', (others => 'X') when others;
  pc_alu <= std_ulogic_vector(unsigned(pc) + unsigned(pc_alu_in));

  process(reset, pc_clk)
  begin
    if (reset = '0') then
      pc <= (others => '0');
    elsif rising_edge(pc_clk) then
      pc <= next_ins;
    end if;
  end process;
end Behavioral;
