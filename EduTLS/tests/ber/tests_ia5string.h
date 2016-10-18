#include "../../src/encoding/ber/ia5string.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_ia5string_short_encode() {
  uint8_t ia5string[17] = "YELLOW SUBMARINE";
  uint8_t encoded[18] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  assert(encode_ia5string_length(16) == 18);
  encode_ia5string(encoded, ia5string, 16);

  assert(encoded[0] == 0x16);
  assert(encoded[1] == 16);
  assert(encoded[2] == 'Y');
  assert(encoded[3] == 'E');
  assert(encoded[4] == 'L');
  assert(encoded[5] == 'L');
  assert(encoded[6] == 'O');
  assert(encoded[7] == 'W');
  assert(encoded[8] == ' ');
  assert(encoded[9] == 'S');
  assert(encoded[10] == 'U');
  assert(encoded[11] == 'B');
  assert(encoded[12] == 'M');
  assert(encoded[13] == 'A');
  assert(encoded[14] == 'R');
  assert(encoded[15] == 'I');
  assert(encoded[16] == 'N');
  assert(encoded[17] == 'E');

  return 0;
}

int test_ber_ia5string_short_decode() {
  uint8_t encoded[18] = {0x16, 16, 'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
  uint8_t ia5string[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  assert(decode_ia5string_length(encoded) == 16);
  decode_ia5string(ia5string, encoded, 18);

  assert(ia5string[0] == 'Y');
  assert(ia5string[1] == 'E');
  assert(ia5string[2] == 'L');
  assert(ia5string[3] == 'L');
  assert(ia5string[4] == 'O');
  assert(ia5string[5] == 'W');
  assert(ia5string[6] == ' ');
  assert(ia5string[7] == 'S');
  assert(ia5string[8] == 'U');
  assert(ia5string[9] == 'B');
  assert(ia5string[10] == 'M');
  assert(ia5string[11] == 'A');
  assert(ia5string[12] == 'R');
  assert(ia5string[13] == 'I');
  assert(ia5string[14] == 'N');
  assert(ia5string[15] == 'E');

  return 0;
}
