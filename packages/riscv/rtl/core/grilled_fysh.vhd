--! \file grilled_fysh.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Hardware-based random number generator.\n

-- Every clock cycle, shift then XOR?
entity grilled_fysh is
  port (
    clk_i  : in  std_ulogic;
    pins_i : in  std_ulogic_vector (7 downto 0);
    gf_o   : out std_ulogic_vector (31 downto 0) := (others => '0'));
end grilled_fysh;

-- 00_00_00_00
-- 00_00_00_11
-- 00_00_11_22
-- 00_11_22_33
-- 11_22_33_44
-- 22_33_44_55

architecture rtl of grilled_fysh is
begin
  shift : process (clk_i)
  begin
    if rising_edge(clk_i) then
      gf_o <= gf_o(23 downto 0) & (gf_o(31 downto 24) xor pins_i);
    end if;
  end process shift;
end rtl;
