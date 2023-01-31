#!/bin/sh
cd build_memory_leak_checking; clear; make && valgrind --leak-check=full --show-reachable=yes -s ./c-utils; cd ..
