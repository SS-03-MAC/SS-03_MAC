#include "../../src/bignum/bigint.h"
#include <cassert>

int test_exponentiation_small() {

  uint8_t e_a[42] = {0x12, 0x49, 0xad, 0x25, 0x94, 0xc3, 0x7c, 0xeb, 0x0b, 0x27, 0x84, 0xc4, 0xce, 0x0b,
                     0xf3, 0x8a, 0xce, 0x40, 0x8e, 0x21, 0x1a, 0x7c, 0xaa, 0xb2, 0x43, 0x08, 0xa8, 0x2e,
                     0x8f, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  BigInt *a = new BigInt(10, false);
  BigInt *b = new BigInt(100, false);
  BigInt *c = a->exp(b);
  BigInt *e = new BigInt(false, e_a, 42);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}

int test_modexp_small() {
  BigInt *a = new BigInt(10, false);
  BigInt *b = new BigInt(100, false);
  BigInt *m = new BigInt(2, false);
  BigInt *e = new BigInt(0, false);
  BigInt *c = a->modexp(b, m);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete m;
  delete e;

  return 0;
}
