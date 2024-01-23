--! \file memory_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Test bench for the high-level memory module.
entity memory_tb is
end memory_tb;

architecture Behavioral of memory_tb is
  component memory is
    port (
      rd_clk_i, mem_clk_i, insn_clk_i, addr_sel_i, reset_i : in std_ulogic;
      sx_size_i                                            : in std_ulogic_vector (2 downto 0);
      rd_sel_i                                             : in std_ulogic_vector (1 downto 0);
      alu_i, pc_i, pc_alu_i                                : in std_ulogic_vector (31 downto 0);

      insn_o          : out std_ulogic_vector (31 downto 0);
      reg_sel_1_val_o : out std_ulogic_vector (31 downto 0);
      reg_sel_2_val_o : out std_ulogic_vector (31 downto 0));
  end component;

  signal rd_clk, mem_clk, insn_clk, addr_sel, reset : std_ulogic;
  signal sx_size                                    : std_ulogic_vector (2 downto 0);
  signal rd_sel                                     : std_ulogic_vector (1 downto 0);
  signal alu, pc, pc_alu                            : std_ulogic_vector (31 downto 0);
  signal insn                                       : std_ulogic_vector (31 downto 0);
  signal rs1_val                                    : std_ulogic_vector (31 downto 0);
  signal rs2_val                                    : std_ulogic_vector (31 downto 0);
begin
  memory_inst : component memory port map (
    rd_clk_i        => rd_clk,
    mem_clk_i       => mem_clk,
    insn_clk_i      => insn_clk,
    addr_sel_i      => addr_sel,
    reset_i         => reset,
    sx_size_i       => sx_size,
    rd_sel_i        => rd_sel,
    alu_i           => alu,
    pc_i            => pc,
    pc_alu_i        => pc_alu,
    insn_o          => insn,
    reg_sel_1_val_o => rs1_val,
    reg_sel_2_val_o => rs2_val);
end Behavioral;
