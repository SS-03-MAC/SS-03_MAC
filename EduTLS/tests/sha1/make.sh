#!/bin/bash

if [ "$(which clang-format)" != "" ]; then
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cpp ./*.h
fi

rm -rf ./a.out.dSYM ./a.out

g++ ./main.cpp ../../src/crypto/hash/*.cpp -Werror -Wall -Wextra -O0 -ggdb -std=c++11
