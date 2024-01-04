library ieee;
use ieee.std_logic_1164.all;

entity memory_tb is
end memory_tb;

architecture Behavioral of memory_tb is
  component memory is
    port (
      rd_clk_i, mem_clk_i, insn_clk_i, addr_sel_i, reset_i : in std_ulogic;
      sx_size_i                                            : in std_ulogic_vector (2 downto 0);
      rd_sel_i                                             : in std_ulogic_vector (1 downto 0);
      alu_i, pc_i, pc_alu_i                                : in std_ulogic_vector (31 downto 0);

      insn_o    : out std_ulogic_vector (31 downto 0);
      rs1_val_o : out std_ulogic_vector (31 downto 0);
      rs2_val_o : out std_ulogic_vector (31 downto 0));
  end component;

  signal rd_clk_s, mem_clk_s, insn_clk_s, addr_sel_s, reset_s : std_ulogic;
  signal sx_size_s                                            : std_ulogic_vector (2 downto 0);
  signal rd_sel_s                                             : std_ulogic_vector (1 downto 0);
  signal alu_s, pc_s, pc_alu_s                                : std_ulogic_vector (31 downto 0);
  signal insn_s                                               : std_ulogic_vector (31 downto 0);
  signal rs1_val_s                                            : std_ulogic_vector (31 downto 0);
  signal rs2_val_s                                            : std_ulogic_vector (31 downto 0);
begin
  memory_u : component memory port map (
    rd_clk_i   => rd_clk_s,
    mem_clk_i  => mem_clk_s,
    insn_clk_i => insn_clk_s,
    addr_sel_i => addr_sel_s,
    reset_i    => reset_s,
    sx_size_i  => sx_size_s,
    rd_sel_i   => rd_sel_s,
    alu_i      => alu_s,
    pc_i       => pc_s,
    pc_alu_i   => pc_alu_s,
    insn_o     => insn_s,
    rs1_val_o  => rs1_val_s,
    rs2_val_o  => rs2_val_s);
end Behavioral;
