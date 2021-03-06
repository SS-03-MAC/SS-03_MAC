#include "../../src/bignum/bigint.h"
#include "../../src/encoding/ber/biginteger.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_bigint_unsigned() {
  uint8_t data[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
  BigInt *input = new BigInt(false, data, 16);
  BigInt *decoded = new BigInt(0, false);
  uint8_t encoded[24] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  encode_bigint(encoded, input);
  size_t e_s = 0;
  while (encoded[e_s] != 0x00) {
    e_s += 1;
  }
  decode_bigint(decoded, encoded, e_s);

  assert(input->cmp(decoded) == 0);

  return 0;
}

int test_ber_bigint_signed() {
  uint8_t data[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
  BigInt *input = new BigInt(true, data, 16);
  BigInt *decoded = new BigInt(0, false);
  uint8_t encoded[24] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  encode_bigint(encoded, input);
  size_t e_s = 0;
  while (encoded[e_s] != 0x00) {
    e_s += 1;
  }
  decode_bigint(decoded, encoded, e_s);
  assert(input->cmp(decoded) == 0);

  return 0;
}
