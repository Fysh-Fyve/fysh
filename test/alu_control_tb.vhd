--! \file alu_control_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

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

  signal insn             : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs1_val, rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  -- Clock Signals
  signal clk     : std_ulogic := '0';
  signal rd_clk  : std_ulogic := '0';
  signal ir_clk  : std_ulogic := '0';
  signal mem_clk : std_ulogic := '0';

  signal alu, pc, pc_alu : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rd_sel          : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal reset, addr_sel : std_ulogic                      := '0';
  signal sx_size         : std_ulogic_vector (2 downto 0)  := (others => '0');
begin
  alu_control_inst : component alu_control port map (
    clk_i      => clk,
    insn_i     => insn,
    rs1_val_i  => rs1_val,
    rs2_val_i  => rs2_val,
    reset_o    => reset,
    alu_o      => alu,
    pc_o       => pc,
    pc_alu_o   => pc_alu,
    addr_sel_o => addr_sel,
    rd_clk_o   => rd_clk,
    ir_clk_o   => ir_clk,
    mem_clk_o  => mem_clk,
    rd_sel_o   => rd_sel,
    sx_size_o  => sx_size);
end Behavioral;
