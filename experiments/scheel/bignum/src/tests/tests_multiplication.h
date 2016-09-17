#include "../lib/bigint.h"
#include <cassert>

int test_multiplication_small() {
  uint64_t a_i = 1;
  uint64_t b_i = 1;
  uint64_t r_i = 1;

  for (a_i = 1; a_i < 100; a_i++) {
    for (b_i = 1; b_i < 100; b_i++) {
      r_i = a_i * b_i;
      BigInt *a = new BigInt(a_i, false);
      BigInt *b = new BigInt(b_i, false);
      BigInt *c = a->mul(b);
      BigInt *e = new BigInt(r_i, false);

      assert(e->equals(c));

      delete a;
      delete b;
      delete c;
      delete e;
    }
  }

  return 0;
}

int test_multiplication_overflow() {
  uint8_t a_a[11] = {0xFF, 0x12, 0xFF, 0x34, 0xFF, 0x56, 0xFF, 0x67, 0xFF, 0x89, 0xFF};
  uint8_t b_a[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
  uint8_t e_a[27] = {0x01, 0x22, 0x37, 0xbf, 0x61, 0xd8, 0x90, 0x7e, 0xae, 0x25, 0xdc, 0xc8, 0xcb, 0xb6,
                     0x4c, 0x46, 0xb8, 0x49, 0xfb, 0x77, 0xd2, 0x71, 0x23, 0x3a, 0x98, 0x6d, 0xf0};
  BigInt *a = new BigInt(false, a_a, 11);
  BigInt *b = new BigInt(false, b_a, 16);
  BigInt *c = b->mul(a);
  BigInt *e = new BigInt(false, e_a, 27);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}
