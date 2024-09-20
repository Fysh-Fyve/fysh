#!/bin/sh

TEED=$(mktemp -p /tmp)
make && ./build/fysh-sea -n ./examples/fib.fysh | tee $TEED | llc-18
python -c 'print("-" * 80)'
cat $TEED
rm $TEED
