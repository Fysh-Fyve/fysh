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
    x"000087b7",  -- lui   x15, 0x8     // x15 = 0x00008000
    x"12345117",  -- auipc  x2, 0x12345 // x2  = 0x00000004 + 0x12345000 = 0x12345004
    x"00a10093",  -- addi   x1, x2, 10  // x1  = 0x12345004 + 0x0000000a = 0x1234500e
    x"4027da13",  -- srai  x20, x15, 2  // x20 = 0x00008000 >> 2 = 0x00002000
    x"00f100b3",  -- add    x1, x2, x15 // x1  = 0x12345004 + 0x00008000 = 0x1234d004
    x"402a00b3",  -- sub    x1, x20, x2 // x1  = 0x00002000 - 0x12345004 = 0xedcbcffc
    others => (31 downto 0 => '0')
    );
end package rom;
