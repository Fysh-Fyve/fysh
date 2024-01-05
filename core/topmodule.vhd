library ieee;
use ieee.std_logic_1164.all;

entity topmodule is
  port (clk : in std_ulogic);
end topmodule;

architecture Behavioral of topmodule is
  component alu_control is
    port (
      clk_i                : in std_ulogic;
      insn_i               : in std_ulogic_vector (31 downto 0);
      rs1_val_i, rs2_val_i : in std_ulogic_vector (31 downto 0);

      alu_o, pc_o, pc_alu_o                              : out std_ulogic_vector (31 downto 0);
      reset_o, addr_sel_o, rd_clk_o, mem_clk_o, ir_clk_o : out std_ulogic;
      rd_sel_o                                           : out std_ulogic_vector (1 downto 0);
      sx_size_o                                          : out std_ulogic_vector (2 downto 0));
  end component;

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

  signal insn_s               : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs1_val_s, rs2_val_s : std_ulogic_vector (31 downto 0) := (others => '0');

  signal alu_s, pc_s, pc_alu_s                              : std_ulogic_vector (31 downto 0) := (others => '0');
  signal reset_s, addr_sel_s, rd_clk_s, mem_clk_s, ir_clk_s : std_ulogic                      := '0';
  signal rd_sel_s                                           : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal sx_size_s                                          : std_ulogic_vector (2 downto 0)  := (others => '0');
begin
  alu_control_u : component alu_control port map (
    clk_i      => clk,
    insn_i     => insn_s,
    rs1_val_i  => rs1_val_s,
    rs2_val_i  => rs2_val_s,
    alu_o      => alu_s,
    pc_o       => pc_s,
    pc_alu_o   => pc_alu_s,
    reset_o    => reset_s,
    addr_sel_o => addr_sel_s,
    rd_clk_o   => rd_clk_s,
    mem_clk_o  => mem_clk_s,
    ir_clk_o   => ir_clk_s,
    rd_sel_o   => rd_sel_s,
    sx_size_o  => sx_size_s);

  memory_u : component memory port map (
    rd_clk_i   => rd_clk_s,
    mem_clk_i  => mem_clk_s,
    insn_clk_i => ir_clk_s,
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
