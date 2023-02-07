#!/bin/sh

#
# Remove the old build if exists
#
rm -rf ./build

#
# Run cmake to generate all files
#
cmake -S ./cmake_memory_leak_checking -B ./build_memory_leak_checking \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_FLAGS="-std=gnu17" \
    -DCMAKE_BUILD_TYPE=Debug

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./build_memory_leak_checking/compile_commands.json ./build

