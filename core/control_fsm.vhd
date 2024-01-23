--! \file control_fsm.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! The Big Brain of the CPU.\n

--! TODO: Implement
entity control_fsm is
  port (
    --! Clock Signal.
    clk_i                   : in std_ulogic;
    --! Equal flag (A == B).
    eq_i                    : in std_ulogic;
    --! Less than flag (A < B).
    lt_i                    : in std_ulogic;
    --! Unsigned less than flag (A < B (unsigned)).
    ltu_i                   : in std_ulogic;
    opcode_i                : in std_ulogic_vector (6 downto 0);
    op_bits_i               : in std_ulogic_vector (2 downto 0);
    add_shift_modify_flag_i : in std_ulogic;

    add_shift_modify_flag_o                 : out std_ulogic;
    op_bits_o, sx_size_o                    : out std_ulogic_vector (2 downto 0);
    addr_sel_o, alu_a_sel_o, alu_b_sel_o    : out std_ulogic;
    rd_sel_o                                : out std_ulogic_vector (1 downto 0);
    mem_clk_o, rd_clk_o, pc_clk_o, ir_clk_o : out std_ulogic := '0';
    pc_alu_sel_o, pc_next_sel_o             : out std_ulogic;
    reset_o                                 : out std_logic);
end control_fsm;

architecture Behavioral of control_fsm is
begin
  drive_clock : process(clk_i)
  begin
    if rising_edge(clk_i) then
      pc_clk_o <= not pc_clk_o;
      ir_clk_o <= not ir_clk_o;
    end if;
  end process drive_clock;
end Behavioral;
