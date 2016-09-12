#!/bin/bash

clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cc ./*/*.h

g++ ./main.cc -Werror -Wall -Wextra -O0 -ggdb
