#include "../../src/bignum/bigint.h"
#include <cassert>

int test_modinv() {
  BigInt *a = new BigInt(207, false);
  BigInt *m = new BigInt(790, false);
  BigInt *c = a->modinv(m);
  BigInt *e = new BigInt(603, false);
  assert(e->equals(c));

  delete a;
  delete m;
  delete c;
  delete e;

  return 0;
}
