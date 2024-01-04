library ieee;
use ieee.std_logic_1164.all;

entity alu_control_tb is
end alu_control_tb;

architecture Behavioral of alu_control_tb is
  component alu_control is
    port (
      clk_i                : in std_ulogic;
      insn_i               : in std_ulogic_vector (31 downto 0);
      rs1_val_i, rs2_val_i : in std_ulogic_vector (31 downto 0);

      alu_o, pc_o, pc_alu_o         : out std_ulogic_vector (31 downto 0);
      reset_o, addr_sel_o           : out std_ulogic;
      rd_clk_o, mem_clk_o, ir_clk_o : out std_ulogic;
      rd_sel_o                      : out std_ulogic_vector (1 downto 0);
      sx_size_o                     : out std_ulogic_vector (2 downto 0));
  end component;

  signal insn_s               : std_ulogic_vector (31 downto 0);
  signal rs1_val_s, rs2_val_s : std_ulogic_vector (31 downto 0);

  -- Clock Signals
  signal clk_s     : std_ulogic;
  signal rd_clk_s  : std_ulogic;
  signal ir_clk_s  : std_ulogic;
  signal mem_clk_s : std_ulogic;

  signal alu_s, pc_s, pc_alu_s : std_ulogic_vector (31 downto 0);
  signal rd_sel_s              : std_ulogic_vector (1 downto 0);
  signal reset_s, addr_sel_s   : std_ulogic;
  signal sx_size_s             : std_ulogic_vector (2 downto 0);
begin
  alu_control_u : component alu_control port map (
    clk_i      => clk_s,
    insn_i     => insn_s,
    rs1_val_i  => rs1_val_s,
    rs2_val_i  => rs2_val_s,
    reset_o    => reset_s,
    alu_o      => alu_s,
    pc_o       => pc_s,
    pc_alu_o   => pc_alu_s,
    addr_sel_o => addr_sel_s,
    rd_clk_o   => rd_clk_s,
    ir_clk_o   => ir_clk_s,
    mem_clk_o  => mem_clk_s,
    rd_sel_o   => rd_sel_s,
    sx_size_o  => sx_size_s);
end Behavioral;
