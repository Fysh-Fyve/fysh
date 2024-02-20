#!/bin/sh

[ $# = 0 ] && {
	line=$(cat)
} || {
	line=$1
}
scales=$(echo "obase=2;$line" | bc | tr '1' '{' | tr "0" "(")
echo "><$scales>"
