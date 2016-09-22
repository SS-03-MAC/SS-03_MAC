#!/bin/bash

for i in ./*.cpp ./*.h  ./*/*.cpp ./*/*.h ./*/*/*.cpp ./*/*/*.h; do
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i $i
done

mkdir ../bin

g++ ./client/main.cpp -Werror -Wall -Wextra -O0 -ggdb -o ../bin/edutls-client
