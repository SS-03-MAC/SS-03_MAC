#include "../../src/encoding/ber/boolean.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_boolean_encode() {
  bool t_v = true;
  bool f_v = false;

  uint8_t result[3];

  assert(encode_boolean_length() == 3);
  encode_boolean(result, t_v);
  assert(result[0] == 1);
  assert(result[1] == 1);
  assert(result[2] != 0);
  encode_boolean(result, f_v);
  assert(result[0] == 1);
  assert(result[1] == 1);
  assert(result[2] == 0);

  return 0;
}

int test_ber_boolean_decode() {

  uint8_t t_v[3] = {0x01, 0x01, 0xFF};
  uint8_t t_v2[3] = {0x01, 0x01, 0x01};
  uint8_t f_v[3] = {0x01, 0x01, 0x00};

  bool result;

  assert(decode_boolean_length() == 1);
  decode_boolean(&result, t_v);
  assert(result == true);
  decode_boolean(&result, f_v);
  assert(result == false);
  decode_boolean(&result, t_v2);
  assert(result == true);

  return 0;
}
