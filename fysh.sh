#!/bin/sh
# Translate numbers to fysh, writing to standard output.
# Usage:
#	./fysh.sh [NUMBER]
# With no NUMBER, read standard input.

[ $# = 0 ] && {
	line=$(cat)
} || {
	line=$1
}
scales=$(echo "obase=2;$line" | bc | tr '1' '{' | tr "0" "(")
echo "><$scales°>"
