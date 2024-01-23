--! \file topmodule_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Test bench for the top module.
entity topmodule_tb is
end topmodule_tb;

architecture Behavioral of topmodule_tb is
  component topmodule is port (clk : in std_ulogic);
  end component;

  signal clk : std_ulogic;
begin
  topmodule_inst : component topmodule port map (clk => clk);
end Behavioral;
