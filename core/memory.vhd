library ieee;
use ieee.std_logic_1164.all;

entity memory is
  port (
    mem_clk, insn_clk, addr_sel, reset : in std_ulogic;
    sx_size                            : in std_ulogic_vector (2 downto 0);
    alu, pc, rs2_val                   : in std_ulogic_vector (31 downto 0);

    insn, mem_sx : out std_ulogic_vector (31 downto 0));
end memory;

architecture Behavioral of memory is
  signal addr, mem_out : std_ulogic_vector (31 downto 0);

  component mem is port (
    d_in, read_addr, write_addr : in  std_ulogic_vector (31 downto 0);
    write_en                    : in  std_ulogic;
    d_out                       : out std_ulogic_vector (31 downto 0));
  end component;

  component mbr_sx is port (
    mbr  : in  std_ulogic_vector (31 downto 0);
    size : in  std_ulogic_vector (2 downto 0);
    sx   : out std_ulogic_vector (31 downto 0));
  end component;

begin
  memory : component mem port map (
    read_addr  => addr,
    write_addr => addr,
    write_en   => mem_clk,
    d_in       => rs2_val,
    d_out      => mem_out);

  mbr : component mbr_sx port map (
    size => sx_size,
    mbr  => mem_out,
    sx   => mem_sx);

  addr <= with addr_sel select pc when '1', alu when '0', (others => 'X') when others;

  process(reset, insn_clk)
  begin
    if (reset = '0') then
      insn <= (others => '0');
    elsif rising_edge(insn_clk) then
      insn <= mem_out;
    end if;
  end process;
end Behavioral;
