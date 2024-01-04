library ieee;
use ieee.std_logic_1164.all;

entity memory is
  port (
    mem_clk_i, insn_clk_i, addr_sel_i, reset_i : in std_ulogic;
    sx_size_i                                  : in std_ulogic_vector (2 downto 0);
    alu_i, pc_i, rs2_val_i                     : in std_ulogic_vector (31 downto 0);

    insn_o, mem_sx_o : out std_ulogic_vector (31 downto 0));
end memory;

architecture Behavioral of memory is
  signal addr_s, mem_out_s : std_ulogic_vector (31 downto 0);

  component mem is port (
    d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
    write_en_i                     : in  std_ulogic;
    d_o                            : out std_ulogic_vector (31 downto 0));
  end component;

  component mbr_sx is port (
    mbr_i  : in  std_ulogic_vector (31 downto 0);
    size_i : in  std_ulogic_vector (2 downto 0);
    sx_o   : out std_ulogic_vector (31 downto 0));
  end component;
begin
  mem_u : component mem port map (
    read_addr_i  => addr_s,
    write_addr_i => addr_s,
    write_en_i   => mem_clk_i,
    d_i          => rs2_val_i,
    d_o          => mem_out_s);

  mbr_sx_u : component mbr_sx port map (
    mbr_i  => mem_out,
    size_i => sx_size,
    sx_o   => mem_sx_o);

  with addr_sel_i select addr_s <=
    pc_i            when '1',
    alu_i           when '0',
    (others => 'X') when others;

  insn_register_p : process(reset_i, insn_clk_i)
  begin
    if (reset_i = '0') then
      insn_o <= (others => '0');
    elsif rising_edge(insn_clk_i) then
      insn_o <= mem_out_s;
    end if;
  end process insn_register_p;
end Behavioral;
