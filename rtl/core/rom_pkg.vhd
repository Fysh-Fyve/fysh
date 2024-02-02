--! \file rom_pkg.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use work.fysh.all;
--! @endcond

--! Package containing the ROM.\n
package rom is
  constant rom_arr : mem_t (0 to ROM_NUM_WORDS-1) := (
  -- Insert mem here
    others => (31 downto 0 => '0')
    );
end package rom;
