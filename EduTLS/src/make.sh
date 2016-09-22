#!/bin/bash

for i in `find -type f | grep -i '\.\(h\|cpp\)$'`; do
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i $i
done

if [ ! -d ../bin ]; then
	mkdir ../bin
fi

g++ ./client/main.cpp ./crypto/symmetric/*.cpp -Werror -Wall -Wextra -O0 -ggdb -o ../bin/edutls-client
