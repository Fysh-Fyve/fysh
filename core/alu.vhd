library ieee;
use ieee.std_logic_1164.all;

entity alu is
  port (
    a, b    : in std_ulogic_vector (31 downto 0);
    func    : in std_ulogic_vector (2 downto 0);
    sub_sra : in std_ulogic;                      -- ADD => SUB, SLA => SRA
    shamt   : in std_ulogic_vector (4 downto 0);  -- Shift amount

    q           : out std_ulogic_vector (31 downto 0);
    eq, lt, ltu : out std_ulogic);      -- A == B, A < B, A < B (unsigned)
end alu;

architecture Behavioral of alu is
begin
end Behavioral;
