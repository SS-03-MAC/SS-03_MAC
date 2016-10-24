#include "../../src/bignum/bigint.h"
#include <cassert>

int test_addition_small() {
  for (int64_t aa = -512; aa <= 512; aa++) {
    for (int64_t bb = -512; bb <= 512; bb++) {
      uint64_t ra = aa;
      if (aa < 0) {
        ra = (uint64_t)(-1 * aa);
      }
      uint64_t rb = bb;
      if (bb < 0) {
        rb = (uint64_t)(-1 * bb);
      }
      uint64_t rc = aa + bb;
      if ((aa + bb) < 0) {
        rc = (uint64_t)(-1 * (aa + bb));
      }
      BigInt *a = new BigInt((uint64_t)ra, (aa < 0));
      BigInt *b = new BigInt((uint64_t)rb, (bb < 0));
      BigInt *c = a->add(b);
      BigInt *e = new BigInt((uint64_t)rc, ((aa + bb) < 0));

      assert(e->equals(c));

      delete a;
      delete b;
      delete c;
      delete e;
    }
  }

  return 0;
}

int test_addition_overflow() {
  BigInt *a = new BigInt(0xFFFFFFFFFFFFFFFF, false);
  BigInt *b = new BigInt(0x10FF, false);
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
