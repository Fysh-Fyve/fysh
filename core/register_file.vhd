library ieee;
use ieee.std_logic_1164.all;

entity register_file is
  port (
    rd_clk : in std_logic;
    reset  : in std_logic;

    rd  : in std_logic_vector (5 downto 0);  -- Register Destination
    rs1 : in std_logic_vector (5 downto 0);  -- Register Source 1
    rs2 : in std_logic_vector (5 downto 0);  -- Register Source 2

    rd_val  : in  std_logic_vector (31 downto 0);
    rs1_val : out std_logic_vector (31 downto 0);
    rs2_val : out std_logic_vector (31 downto 0));
end register_file;

architecture Behavioral of register_file is
begin
end Behavioral;
