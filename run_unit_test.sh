#!/bin/sh
cd build_unit_test; clear; make && GTEST_FAIL_FAST=true ./c-utils-unit-test; cd ..
