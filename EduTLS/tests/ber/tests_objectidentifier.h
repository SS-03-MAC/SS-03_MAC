#include "../../src/encoding/ber/objectidentifier.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_objectidentifier_encode() {
  uint32_t identifier[3] = {2, 100, 3};
  uint8_t result[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

  assert(encode_objectidentifier_length(identifier, 3) == 5);

  encode_objectidentifier(result, identifier, 3);

  assert(result[0] == 0x06);
  assert(result[1] == 0x03);
  assert(result[2] == 0x81);
  assert(result[3] == 0x34);
  assert(result[4] == 0x03);

  return 0;
}

int test_ber_objectidentifier_decode() {
  uint8_t encoded[5] = {0x06, 0x03, 0x81, 0x34, 0x03};
  uint32_t identifier[3] = {0, 0, 0};

  assert(decode_objectidentifier_length(encoded, 5) == 3);

  decode_objectidentifier(identifier, encoded, 5);

  assert(identifier[0] == 2);
  assert(identifier[1] == 100);
  assert(identifier[2] == 3);

  return 0;
}
