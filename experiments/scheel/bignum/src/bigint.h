/*
 * Bignum library
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "bigint_ll.h"

class BigInt {
private:
  bool negative;
  BigIntLL data;

public:
  BigInt() {
    data = BigIntLL();
    this->negative = false;
  }

  BigInt(uint64_t val) {
    this->negative = false;
    data = BigIntLL(val);
  }

  BigInt(const BigInt &val) {
    this->negative = val.negative;
    this->data = BigIntLL(val.data);
  }

  void print() {
    if (!this->negative) {
      printf("+");
    } else {
      printf("-");
    }

    this->data.rev_print();

    printf("\n");
  }

  void add(const BigInt &val) {}

  void shift(uint64_t bits) {}
};
