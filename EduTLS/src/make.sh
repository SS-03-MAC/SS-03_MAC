#!/bin/bash

for i in `find -type f | grep -i '\.\(h\|cpp\)$'`; do
	echo "Formatting $i..."
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i $i
done

if [ ! -d ../bin ]; then
	mkdir ../bin
fi

g++ ./client/main.cpp ./bignum/*.cpp ./crypto/*/*.cpp -Werror -Wall -Wextra  -std=c++11 -O0 -ggdb -o ../bin/edutls-client
