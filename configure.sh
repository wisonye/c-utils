#!/bin/sh
cmake -S ./ -B ./build \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_CXX_FLAGS="-std=gnu++17" \
    -DCMAKE_BUILD_TYPE=Debug
