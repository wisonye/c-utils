#!/bin/sh
OS_NAME=`uname -s`
echo "OS_NAME: ${OS_NAME}"
if [ "${OS_NAME}" == "FreeBSD" ]; then
    cd temp_build/build_memory_leak_checking; clear; make && ./c-utils-demo; cd ..
else
    cd temp_build/build_memory_leak_checking; clear; make && ASAN_OPTIONS=detect_leaks=1 ./c-utils-demo; cd ..
fi
