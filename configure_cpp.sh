#!/bin/sh
cmake -S ./use_cpp_compiler_to_run_googletest -B ./build_unit_test \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_CXX_FLAGS="-std=gnu++17" \
    -DCMAKE_BUILD_TYPE=Debug
