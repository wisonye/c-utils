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
cmake -S ./cmake/unit_test -B ./temp_build/unit_test \
      -DUSE_CUSTOM_UNITY_INSTALL_PATH=true \
      -DMY_UNITY_INSTALL_INCLUDE_PATH=${INSTALL_PREFIX}/include/unity \
      -DMY_UNITY_INSTALL_LIB_PATH=${INSTALL_PREFIX}/lib

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/unit_test/compile_commands.json ./build
