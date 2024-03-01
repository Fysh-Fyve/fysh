#!/bin/sh

{
	cat scripts/rom/rom_pkg.part1.vhd;
	cat "$1" | build/fyve-rom;
	cat scripts/rom/rom_pkg.part2.vhd;
	echo "--! From binary file $1";
	asm_file="${1%.*}.s"
	[ -e "${asm_file}" ] && {
		sed 's/^/--! /' "${asm_file}"
	}
} > rtl/core/rom_pkg.vhd
