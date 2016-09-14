#include "../lib/bigint.h"
#include <cassert>

int test_equality_zeros() {
  BigInt *a = new BigInt(0x00ull);
  BigInt *b = new BigInt(0x00ull);
  b->negate();
  assert(a->equals(b));

  delete a;
  delete b;

  return 0;
}

int test_equality_padding() {
  uint8_t a_a[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
  uint8_t b_a[3] = {0x00, 0x00, 0x01};
  BigInt *a = new BigInt(false, a_a, 6);
  BigInt *b = new BigInt(false, b_a, 3);
  assert(a->equals(b));

  delete a;
  delete b;

  return 0;
}

int test_equality_one() {
  BigInt *a = new BigInt(0x01ull);
  BigInt *b = new BigInt(0x01ull);
  assert(a->equals(b));

  delete a;
  delete b;

  return 0;
}

int test_inequality_one() {
  BigInt *a = new BigInt(0x01ull);
  BigInt *b = new BigInt(0x01ull);
  b->negate();
  assert(!a->equals(b));

  delete a;
  delete b;

  return 0;
}

int test_compare_greater() {
  BigInt *a = new BigInt(0x09ull);
  BigInt *b = new BigInt(0x01ull);
  assert(a->cmp(b) == 1);

  delete a;
  delete b;

  return 0;
}

int test_compare_less() {
  BigInt *a = new BigInt(0x01ull);
  BigInt *b = new BigInt(0x09ull);
  assert(a->cmp(b) == -1);

  delete a;
  delete b;

  return 0;
}

int test_compare_greater_negative() {
  BigInt *a = new BigInt(0x01ull);
  BigInt *b = new BigInt(0x01ull);
  b->negate();
  assert(a->cmp(b) == 1);

  delete a;
  delete b;

  return 0;
}

int test_compare_less_negative() {
  BigInt *a = new BigInt(0x01ull);
  BigInt *b = new BigInt(0x01ull);
  a->negate();
  assert(a->cmp(b) == -1);

  delete a;
  delete b;

  return 0;
}
