#!/bin/sh

#
# Remove the old build if exists
#
rm -rf ./build

#
# Run cmake to generate all files
#
cmake -S ./cmake_unit_test -B ./build_unit_test \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_CXX_FLAGS="-std=gnu++17" \
    -DCMAKE_BUILD_TYPE=Debug

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./build_unit_test/compile_commands.json ./build

