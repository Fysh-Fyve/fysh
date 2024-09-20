#!/bin/sh

echo "-----------------------------------------------------------------"
echo TEST ${TB}
ghdl ${GHDL_FLAGS} $@ -r ${TB} ${RUN_FLAGS}
