/*
 * Bignum library test cases
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include "bigint.h"

int main() {
  printf("a = 0xFFFFFFFFFFFFFFFF:\n");
  BigInt a = BigInt(0xFFFFFFFFFFFFFFFF);
  a.print();

  printf("b = 0x10:\n");
  BigInt b = BigInt(0x10);
  b.print();

  printf("c = ba\n");
  // Appending:
  BigInt c = b.add(a);
  c.print();

  printf("c = -c: \n");
  c.negate();
  c.print();

  printf("d = ba\n");
  BigInt d = b.add(a);
  d.print();

  printf("d = d + c\n");
  d = d.add(c);
  d.print();

  printf("e = -2\n");
  BigInt e = BigInt(0x02);
  e.negate();
  e.print();

  printf("f = 1\n");
  BigInt f = BigInt(0x01);
  f.print();

  printf("g = e + f\n");
  BigInt g = e.add(f);
  g.print();

  printf("h = g + f\n");
  BigInt h = g.add(f);
  h.print();
}
