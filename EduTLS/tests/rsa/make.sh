#!/bin/bash

if [ "$(which clang-format)" != "" ]; then
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cpp ./*.h
fi

rm -rf ./a.out.dSYM ./a.out

g++ -lgmp ./main.cpp ../../src/crypto/asymmetric/*.cpp ../../src/bignum/*.cpp -Werror -Wall -Wextra -O0 -ggdb -std=c++11 -lgmp
