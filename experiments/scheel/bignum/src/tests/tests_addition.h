#include "../lib/bigint.h"
#include <cassert>

int test_addition_small() {
  BigInt *a = new BigInt(0xF0);
  BigInt *b = new BigInt(0x0F);
  BigInt *c = b->add(a);
  BigInt *e = new BigInt(0xFF);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}

int test_addition_overflow() {
  BigInt *a = new BigInt(0xFFFFFFFFFFFFFFFF);
  BigInt *b = new BigInt(0x10FF);
  BigInt *c = b->add(a);
  uint8_t val[9] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xfe};
  BigInt *e = new BigInt(false, val, 9);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}
