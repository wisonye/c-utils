#!/bin/sh
cmake -S ./use_c_compiler_to_run_main -B ./build_c \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_FLAGS="-std=gnu17" \
    -DCMAKE_BUILD_TYPE=Debug
