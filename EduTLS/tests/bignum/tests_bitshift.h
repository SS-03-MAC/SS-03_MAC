#include "../../src/bignum/bigint.h"
#include <cassert>

int test_left_shift_small() {
  uint64_t i = 0;
  for (i = 0; i < 62; i++) {
    BigInt *a = new BigInt(0x01, false);
    a->left_shift(i);
    BigInt *e = new BigInt((((uint64_t)1) << i), false);

    assert(e->equals(a));

    delete a;
    delete e;
  }

  return 0;
}

int test_right_shift_small() {
  uint64_t i = 0;
  uint64_t base = 0x8000000000000000;
  for (i = 0; i < 64; i++) {
    BigInt *a = new BigInt(base, false);
    a->right_shift(i);
    BigInt *e = new BigInt(base >> i, false);

    assert(e->equals(a));

    delete a;
    delete e;
  }

  return 0;
}
