--! \file mbr_sx.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Takes a value from memory and outputs its sign-extended value.\n

--! I think it's also supposed to combine from multiple reads?
entity mbr_sx is
  port (
    mbr_i  : in  std_ulogic_vector (31 downto 0);
    size_i : in  std_ulogic_vector (2 downto 0);
    sx_o   : out std_ulogic_vector (31 downto 0));
end mbr_sx;

architecture rtl of mbr_sx is
  signal half_sx : std_ulogic_vector(15 downto 0) := (others => '0');
  signal byte_sx : std_ulogic_vector(23 downto 0) := (others => '0');
begin
  half_sx <= (others => mbr_i(15));
  byte_sx <= (others => mbr_i(7));
  with size_i select sx_o <=
    -- TODO: IDK what this is
    mbr_i                        when "000",  -- word
    half_sx & mbr_i(15 downto 0) when "010",  -- halfword
    byte_sx & mbr_i(7 downto 0)  when "100",  -- byte
    (others => 'X')              when others;
end rtl;
