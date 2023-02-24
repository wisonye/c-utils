#!/bin/sh

#
# Remove everything exists
#
./remove_all_cmake_build_folders.sh

#
# Run cmake to generate all files
#
cmake -S ./cmake -B ./temp_build/build_memory_leak_checking \
    -DUSE_VALGRIND=ON

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/build_memory_leak_checking/compile_commands.json ./build


