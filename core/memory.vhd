library ieee;
use ieee.std_logic_1164.all;

entity memory is
  port (
    rd_clk_i, mem_clk_i, insn_clk_i, addr_sel_i, reset_i : in std_ulogic;
    sx_size_i                                            : in std_ulogic_vector (2 downto 0);
    rd_sel_i                                             : in std_ulogic_vector (1 downto 0);
    alu_i, pc_i, pc_alu_i                                : in std_ulogic_vector (31 downto 0);

    insn_o    : out std_ulogic_vector (31 downto 0);
    rs1_val_o : out std_ulogic_vector (31 downto 0);
    rs2_val_o : out std_ulogic_vector (31 downto 0));
end memory;

architecture Behavioral of memory is
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

  component register_file is
    port (
      rd_clk_i : in std_ulogic;
      reset_i  : in std_ulogic;

      rd_i  : in std_ulogic_vector (4 downto 0);  -- Register Destination
      rs1_i : in std_ulogic_vector (4 downto 0);  -- Register Source 1
      rs2_i : in std_ulogic_vector (4 downto 0);  -- Register Source 2

      rd_val_i  : in  std_ulogic_vector (31 downto 0);
      rs1_val_o : out std_ulogic_vector (31 downto 0);
      rs2_val_o : out std_ulogic_vector (31 downto 0));
  end component;

  signal rd_val                : std_ulogic_vector (31 downto 0);
  signal addr, mem_out, mem_sx : std_ulogic_vector (31 downto 0);

begin
  mem_inst : component mem port map (
    read_addr_i  => addr,
    write_addr_i => addr,
    write_en_i   => mem_clk_i,
    d_i          => rs2_val_o,
    d_o          => mem_out);

  mbr_sx_inst : component mbr_sx port map (
    mbr_i  => mem_out,
    size_i => sx_size_i,
    sx_o   => mem_sx);

  register_file_inst : component register_file port map (
    rd_clk_i  => rd_clk_i,
    reset_i   => reset_i,
    rd_i      => insn_o(24 downto 20),
    rs1_i     => insn_o(19 downto 15),
    rs2_i     => insn_o(24 downto 20),
    rd_val_i  => rd_val,
    rs1_val_o => rs1_val_o,
    rs2_val_o => rs2_val_o);

  with addr_sel_i select addr <=
    pc_i            when '1',
    alu_i           when '0',
    (others => 'X') when others;

  with rd_sel_i select rd_val <=
    mem_sx          when "11",
    (others => 'X') when "10",
    alu_i           when "01",
    pc_alu_i        when "00",
    (others => 'X') when others;

  insn_register : process(reset_i, insn_clk_i)
  begin
    if (reset_i = '0') then
      insn_o <= (others => '0');
    elsif rising_edge(insn_clk_i) then
      insn_o <= mem_out;
    end if;
  end process insn_register;
end Behavioral;
