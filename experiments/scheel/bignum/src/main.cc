/*
 * Bignum library test cases
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include "bignum.h"

int main() {
  BigInt a = BigInt(10);
  a.print();

  BigInt b = BigInt(a);
  b.print();

  b.add(a);
  b.print();
}
