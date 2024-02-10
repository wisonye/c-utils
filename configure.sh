#!/bin/sh

OS_TYPE=`uname -s`
echo ">>> OS_TYPE: ${OS_TYPE}"

INSTALL_PREFIX="/home/${USER}/my-installed"

if [ "${OS_TYPE}" = "Darwin" ]; then
    INSTALL_PREFIX="/Users/${USER}/my-installed"
fi

if [ "${OS_TYPE}" = "FreeBSD" ]; then
    INSTALL_PREFIX="/home/${USER}/my-installed"
fi

echo ">>> INSTALL_PREFIX: ${INSTALL_PREFIX}"

#
# Remove everything exists
#
./remove_all_cmake_build_folders.sh

#
# Run cmake to generate all files
#
cmake -S ./cmake -B ./temp_build/build_memory_leak_checking \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/build_memory_leak_checking/compile_commands.json ./build
