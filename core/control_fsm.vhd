library ieee;
use ieee.std_logic_1164.all;

entity control_fsm is
  port (
    clk         : in std_ulogic;
    eq, lt, ltu : in std_ulogic;        -- A == B, A < B, A < B (unsigned)
    opcode      : in std_ulogic_vector (6 downto 0);
    funct3      : in std_ulogic_vector (2 downto 0);
    sub_sra_in  : in std_ulogic;

    sub_sra                         : out std_ulogic;
    func, sx_size                   : out std_ulogic_vector (2 downto 0);
    addr_sel, alu_a_sel, alu_a_sel  : out std_ulogic;
    rd_sel                          : out std_ulogic_vector (1 downto 0);
    mem_clk, rd_clk, pc_clk, ir_clk : out std_ulogic;
    pc_alu_sel, pc_next_sel         : out std_ulogic;
    reset                           : out std_logic);
end control_fsm;

architecture Behavioral of control_fsm is
begin
end Behavioral;
