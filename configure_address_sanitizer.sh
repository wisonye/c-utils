#!/bin/sh

OS_TYPE=`uname -s`
echo ""
echo ">>> OS_TYPE: ${OS_TYPE}"

INSTALL_PREFIX="${HOME}/my-installed"

echo ">>> INSTALL_PREFIX: ${INSTALL_PREFIX}"
echo ""

#
# Remove everything exists
#
./remove_all_cmake_build_folders.sh

#
# Run cmake to generate all files
#
LLVM_CLANG=$(which clang)
cmake -S ./cmake -B ./temp_build/build_memory_leak_checking \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DUSE_ADDRESS_SANITIZER=ON \
    -DCMAKE_C_COMPILER="${LLVM_CLANG}"

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/build_memory_leak_checking/compile_commands.json ./build
