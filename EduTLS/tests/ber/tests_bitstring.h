#include "../../src/encoding/ber/bitstring.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_bitstring_short_encode() {
  uint8_t bitstring[3] = {0x42, 0x21, 0x45};
  uint8_t encoded[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

  assert(encode_bitstring_length(3) == 5);
  encode_bitstring(encoded, bitstring, 3);

  assert(encoded[0] == 0x03);
  assert(encoded[1] == 0x03);
  assert(encoded[2] == 0x42);
  assert(encoded[3] == 0x21);
  assert(encoded[4] == 0x45);

  return 0;
}

int test_ber_bitstring_short_decode() {
  uint8_t encoded[5] = {0x03, 0x03, 0x42, 0x21, 0x45};
  uint8_t bitstring[3] = {0x00, 0x00, 0x00};

  assert(decode_bitstring_length(encoded) == 3);
  assert(encoded[0] = 0x03);
  assert(encoded[1] = 0x03);
  decode_bitstring(bitstring, encoded, 5);

  assert(bitstring[0] == 0x42);
  assert(bitstring[1] == 0x21);
  assert(bitstring[2] == 0x45);

  return 0;
}
