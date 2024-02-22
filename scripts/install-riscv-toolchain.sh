#!/bin/sh

riscv="xpack-riscv-none-elf-gcc-13.2.0-2-linux-x64"
archive="$riscv.tar.gz"

wget -O "/tmp/$archive" "https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v13.2.0-2/$archive"

mkdir -p "$HOME/.local"
cd "$HOME/.local"
tar xzf "/tmp/$archive"
mv "$riscv" riscv-none-elf-gcc

echo 'Add this to your ~/.bashrc:'
echo
echo "export PATH=\"\$HOME/.local/riscv-none-elf-gcc/bin:\$PATH\""
