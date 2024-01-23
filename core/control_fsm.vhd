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
    clk_i                   : in std_ulogic; --! Clock Signal.
    eq_i                    : in std_ulogic; --! Equal flag (A == B).
    lt_i                    : in std_ulogic; --! Less than flag (A < B).
    ltu_i                   : in std_ulogic; --! Unsigned less than flag (A < B (unsigned)).
    opcode_i                : in std_ulogic_vector (6 downto 0);
    op_bits_i               : in std_ulogic_vector (2 downto 0);
    sub_sra_i               : in std_ulogic; -- subtract or shift right arithmetic flag (0 = add, logical shift right; 1 = subtract, arithmetic shift right).

    sub_sra_o                               : out std_ulogic;
    op_bits_o, sx_size_o                    : out std_ulogic_vector (2 downto 0);
    addr_sel_o, alu_a_sel_o, alu_b_sel_o    : out std_ulogic;
    rd_sel_o                                : out std_ulogic_vector (1 downto 0);
    mem_clk_o, rd_clk_o, pc_clk_o, ir_clk_o : out std_ulogic := '0';
    pc_alu_sel_o, pc_next_sel_o             : out std_ulogic;
    reset_o                                 : out std_logic);
end control_fsm;

architecture Behavioral of control_fsm is
signal pc_clk, ir_clk : std_ulogic := '0';
begin
  drive_clock : process(clk_i)
  begin
    if rising_edge(clk_i) then
      pc_clk   <= not pc_clk;
      ir_clk   <= not ir_clk;
    end if;
    pc_clk_o <= pc_clk;
    ir_clk_o <= ir_clk;
  end process drive_clock;
end Behavioral;
