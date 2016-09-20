#!/bin/bash

if [ "$(which clang-format)" != "" ]; then
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cc ./*.h
fi

rm -rf ./a.out.dSYM ./a.out

g++ ./main.cpp ../../src/bignum/*.cpp -Werror -Wall -Wextra -O0 -ggdb -std=c++11
