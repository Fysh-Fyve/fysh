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
    clk  : in  std_ulogic;
    pins : in  std_ulogic_vector (7 downto 0);
    gf_o : out std_ulogic_vector (31 downto 0));
end grilled_fysh;

architecture rtl of grilled_fysh is
begin
  shift : process (clk)
  begin
    if rising_edge(clk) then
      -- TODO: Shift every clock cycle
      gf_o <= pins &pins & pins & pins;
    end if;
  end process shift;
end rtl;
