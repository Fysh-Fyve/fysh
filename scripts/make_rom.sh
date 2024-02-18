#!/bin/sh

{
	cat scripts/rom/rom_pkg.part1.vhd;
	cat "$1" | build/fyve-rom;
	cat scripts/rom/rom_pkg.part2.vhd;
} > rtl/core/rom_pkg.vhd
