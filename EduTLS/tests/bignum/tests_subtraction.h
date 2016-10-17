#include "../../src/bignum/bigint.h"
#include <cassert>

int test_subtraction_small() {
  BigInt *a = new BigInt(0xF0, false);
  BigInt *b = new BigInt(0x0F, false);
  BigInt *c = b->add(a);
  BigInt *e = new BigInt(0xE1, false);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}

int test_subtraction_overflowed() {
  uint8_t a_a[14] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
  uint8_t e_a[14] = {0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0a};
  BigInt *a = new BigInt(false, a_a, 14);
  BigInt *b = new BigInt(0x1234567890, false);
  BigInt *c = b->add(a);
  BigInt *e = new BigInt(false, e_a, 14);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}
