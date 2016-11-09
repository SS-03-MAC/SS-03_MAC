#include "../../src/bignum/bigint.h"
#include <cassert>

int test_subtraction_small() {
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
      uint64_t rc = aa - bb;
      if ((aa - bb) < 0) {
        rc = (uint64_t)(-1 * (aa - bb));
      }
      BigInt *a = new BigInt((uint64_t)ra, (aa < 0));
      BigInt *b = new BigInt((uint64_t)rb, (bb < 0));
      BigInt *c = a->sub(b);
      BigInt *e = new BigInt((uint64_t)rc, ((aa - bb) < 0));

      assert(e->equals(c));

      delete a;
      delete b;
      delete c;
      delete e;
    }
  }

  return 0;
}

int test_subtraction_overflow() {
  uint8_t a_a[14] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
  uint8_t e_a[14] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x11, 0x11, 0x11, 0x11, 0x1b};
  BigInt *a = new BigInt(false, a_a, 14);
  BigInt *b = new BigInt(0x1234567890, false);
  BigInt *c = b->sub(a);
  BigInt *e = new BigInt(true, e_a, 14);

  assert(e->equals(c));

  delete a;
  delete b;
  delete c;
  delete e;

  return 0;
}
