--! \file gpio_pins.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! GPIO Pins.\n

--! From ya boi Jippity
--! Data Flow:
--!   - Data should be read from pin_read_o.
--!   - Data should be written to pin_write_i.
--!
--! Pin Mode Determination:
--!   - Pin mode is determined by pin_mode_i, which is a bit mask.
--!   - Each bit in pin_mode_i corresponds to a specific pin:
--!     - 1 indicates the pin is active (enabled).
--!     - 0 indicates the pin is inactive (disabled).
--!
--! Applying Writes:
--!   - When writing to pin_write_i:
--!     - Data should only be applied to gp_io if the corresponding bit in pin_mode_i is 1.
--!     - The write operation should be masked by pin_mode_i.
entity gpio_pins is
  port (
    clk_i           : in    std_ulogic;  --! Clock signal.
    gp_io           : inout std_ulogic_vector (31 downto 0);  --! In-out port corresponding to the actual pins.
    write_en_i      : in    std_ulogic;  --! Whether to write to pin_write_i
    mode_write_en_i : in    std_ulogic;  --! Whether to write to pin_mode_i
    pin_mode_i      : in    std_ulogic_vector (31 downto 0);  --! Bit mask for writing to GPIO
    pin_write_i     : in    std_ulogic_vector (31 downto 0);  --! Input port for GPIO
    pin_read_o      : out   std_ulogic_vector (31 downto 0);  --! Output port for GPIO
    mode_o          : out   std_ulogic_vector (31 downto 0));  --! Outputs current pin mode
end gpio_pins;

architecture rtl of gpio_pins is
begin
  gpio : process(clk_i)
  begin
    -- TODO: Implement
    if rising_edge(clk_i) then
      pin_read_o <= gp_io;
      gp_io      <= pin_write_i;
    end if;
  end process gpio;
end rtl;
