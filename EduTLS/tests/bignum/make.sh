#!/bin/bash

clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cc ./*.h

rm -rf ./a.out.dSYM ./a.out

g++ ./main.cc ../../src/bignum/*.cc -Werror -Wall -Wextra -O0 -ggdb
