#!/bin/sh
cd temp_build/build_memory_leak_checking; clear; make && ASAN_OPTIONS=detect_leaks=1 ./c-utils-demo; cd ..
