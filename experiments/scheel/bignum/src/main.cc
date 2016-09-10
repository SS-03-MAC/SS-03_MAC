/*
 * Bignum library test cases
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include "bigint.h"

int main() {
  BigInt a = BigInt(0xFFFFFFFFFFFFFFFF);
  a.print();

  BigInt b = BigInt(0x10);
  b.print();

  // Appending:
  BigInt c = b.add(a);
  c.print();

  for (size_t i = 0; i < 1; i++) {
    c = c.add(c);
  }
  c.print();
}
