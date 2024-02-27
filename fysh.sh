#!/bin/sh
# Translate numbers to fysh, writing to standard output.
# Usage:
#	./fysh.sh [NUMBER]
# With no NUMBER, read standard input.

[ $# = 0 ] && { line=$(cat); } || { line=$1; }
trunc=${line#-}
scales=$(echo "obase=2;${trunc}" | bc)
case $line in
	-*) echo "<°$(echo "$scales" | tr '1' '}' | tr '0' ')')><" ;;
	*) echo "><$(echo "$scales" | tr '1' '{' | tr '0' '(')°>" ;;
esac
