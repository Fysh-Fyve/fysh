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
  generic (VERBOSE : boolean := false);
  port (
    clk_i           : in    std_ulogic;  --! Clock signal.
    gp_io           : inout std_ulogic_vector (31 downto 0) := (others => '0');  --! In-out port corresponding to the actual pins.
    write_en_i      : in    std_ulogic;  --! Whether to write to pin_write_i
    mode_write_en_i : in    std_ulogic;  --! Whether to write to pin_mode_i
    pin_mode_i      : in    std_ulogic_vector (31 downto 0);  --! Bit mask for writing to GPIO
    pin_write_i     : in    std_ulogic_vector (31 downto 0);  --! Input port for GPIO
    pin_read_o      : out   std_ulogic_vector (31 downto 0);  --! Output port for GPIO
    mode_o          : out   std_ulogic_vector (31 downto 0));  --! Outputs current pin mode
end gpio_pins;

architecture rtl of gpio_pins is
begin
  verbose_gpio_print :
  if VERBOSE generate
    print_gpio_g :
    for i in 0 to 31 generate
      print_event : process(gp_io)
        use std.textio.all;
        variable l : line;
      begin
        if gp_io(i)'event then
          write(l, string'("gpio "));
          write(l, i);
          write(l, string'(": "));
          write(l, gp_io(i));
          writeline(output, l);
        end if;
      end process;
    end generate print_gpio_g;
  end generate verbose_gpio_print;

  gpio : process(clk_i)
  begin
    -- This basically are just output pins right now
    -- TODO: Implement masking to be able to take input
    if falling_edge(clk_i) then
      pin_read_o <= gp_io;
      if write_en_i then
        gp_io <= pin_write_i;
      end if;
    end if;
  end process gpio;
end rtl;
