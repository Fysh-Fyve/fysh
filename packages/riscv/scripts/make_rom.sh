#!/bin/sh

{
	cat scripts/rom_pkg.part1.vhd;
	cat "$1" | build/fyve-rom;
	cat scripts/rom_pkg.part2.vhd;
	echo "--! From binary file $1";
	asm_file="${1%.*}.s"
	fysh_file="${1%.*}.fysh"
	[ -e "${asm_file}" ] && {
		sed 's/^/--! /' "${asm_file}"
	} || true
	[ -e "${fysh_file}" ] && {
		sed 's/^/--! /' "${fysh_file}"
	} || true
} > rtl/core/rom_pkg.vhd
