#!/bin/sh
# Installs all required packages to build the document

[ "$(id -u)" != "0" ] && {
	cmd=sudo
}

$cmd apt update
$cmd apt -y upgrade
$cmd apt install -y pandoc pandoc-citeproc texlive-xetex texlive-fonts-recommended textlive-extra-utils --no-install-recommends

