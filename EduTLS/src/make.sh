#!/bin/bash

for i in ./*.cpp ./*.h  ./*/*.cpp ./*/*.h ./*/*/*.cpp ./*/*/*.h; do
	clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i $i
done

if [ ! -d ../bin ]; then
  mkdir ../bin
fi

g++ ./client/main.cpp ./crypto/symmetric/aes.cpp -Werror -Wall -Wextra -O0 -ggdb -o ../bin/edutls-client
