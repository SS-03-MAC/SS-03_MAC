#!/bin/bash

clang-format -style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i ./*.cc ./*.h

c++ ./main.cc
