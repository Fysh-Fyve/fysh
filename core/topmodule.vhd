--! \file topmodule.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! The top module that brings all the components together.\n
entity topmodule is
  port (clk : in std_ulogic);
end topmodule;

architecture Behavioral of topmodule is
  component alu_control is
    port (
      clk_i                            : in std_ulogic;
      instruction_i                    : in std_ulogic_vector (31 downto 0);
      reg_val_1_i, reg_val_2_i         : in std_ulogic_vector (31 downto 0); --! The values from selected registers.

      alu_o           : out std_ulogic_vector (31 downto 0);
      pc_o            : out std_ulogic_vector (31 downto 0);
      pc_alu_result_o : out std_ulogic_vector (31 downto 0);
      reset_o         : out std_ulogic;
      addr_sel_o      : out std_ulogic;
      rd_clk_o        : out std_ulogic;
      mem_clk_o       : out std_ulogic;
      ir_clk_o        : out std_ulogic;
      rd_sel_o        : out std_ulogic_vector (1 downto 0);
      sx_size_o       : out std_ulogic_vector (2 downto 0));
  end component;

  component memory is
    port (
      rd_clk_i, mem_clk_i, insn_clk_i, addr_sel_i, reset_i : in std_ulogic;
      sx_size_i                                            : in std_ulogic_vector (2 downto 0);
      rd_sel_i                                             : in std_ulogic_vector (1 downto 0);
      alu_i, pc_i, pc_alu_i                                : in std_ulogic_vector (31 downto 0);

      insn_o          : out std_ulogic_vector (31 downto 0);
      reg_val_1_o : out std_ulogic_vector (31 downto 0);
      reg_val_2_o : out std_ulogic_vector (31 downto 0));
  end component;

  signal insn             : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs1_val, rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  signal alu, pc, pc_alu                          : std_ulogic_vector (31 downto 0) := (others => '0');
  signal reset, addr_sel, rd_clk, mem_clk, ir_clk : std_ulogic                      := '0';
  signal rd_sel                                   : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal sx_size                                  : std_ulogic_vector (2 downto 0)  := (others => '0');
begin
  alu_control_inst : component alu_control port map (
    clk_i           => clk,
    instruction_i   => insn,
    reg_val_1_i     => rs1_val,
    reg_val_2_i     => rs2_val,
    alu_o           => alu,
    pc_o            => pc,
    pc_alu_result_o => pc_alu,
    reset_o         => reset,
    addr_sel_o      => addr_sel,
    rd_clk_o        => rd_clk,
    mem_clk_o       => mem_clk,
    ir_clk_o        => ir_clk,
    rd_sel_o        => rd_sel,
    sx_size_o       => sx_size);

  memory_inst : component memory port map (
    rd_clk_i        => rd_clk,
    mem_clk_i       => mem_clk,
    insn_clk_i      => ir_clk,
    addr_sel_i      => addr_sel,
    reset_i         => reset,
    sx_size_i       => sx_size,
    rd_sel_i        => rd_sel,
    alu_i           => alu,
    pc_i            => pc,
    pc_alu_i        => pc_alu,
    insn_o          => insn,
    reg_val_1_o     => rs1_val,
    reg_val_2_o     => rs2_val);
end Behavioral;
