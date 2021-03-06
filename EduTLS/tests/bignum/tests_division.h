#include "../../src/bignum/bigint.h"
#include <cassert>

int test_division_small() {
  uint64_t a_i = 1;
  uint64_t b_i = 1;
  uint64_t r_i = 1;

  for (a_i = 1; a_i < 100; a_i++) {
    for (b_i = 1; b_i < 100; b_i++) {
      r_i = a_i / b_i;
      BigInt *a = new BigInt(a_i, false);
      BigInt *b = new BigInt(b_i, false);
      BigInt *c = a->div(b);
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
