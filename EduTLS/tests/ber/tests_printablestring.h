#include "../../src/encoding/ber/printablestring.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_printablestring_short_encode() {
  char printablestring[17] = "YELLOW SUBMARINE";
  uint8_t encoded[18] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  assert(encode_printablestring_length(16) == 18);
  encode_printablestring(encoded, printablestring, 16);

  assert(encoded[0] == 0x13);
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

int test_ber_printablestring_short_decode() {
  uint8_t encoded[18] = {0x13, 16, 'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
  char printablestring[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  assert(decode_printablestring_length(encoded) == 16);
  decode_printablestring(printablestring, encoded, 18);

  assert(printablestring[0] == 'Y');
  assert(printablestring[1] == 'E');
  assert(printablestring[2] == 'L');
  assert(printablestring[3] == 'L');
  assert(printablestring[4] == 'O');
  assert(printablestring[5] == 'W');
  assert(printablestring[6] == ' ');
  assert(printablestring[7] == 'S');
  assert(printablestring[8] == 'U');
  assert(printablestring[9] == 'B');
  assert(printablestring[10] == 'M');
  assert(printablestring[11] == 'A');
  assert(printablestring[12] == 'R');
  assert(printablestring[13] == 'I');
  assert(printablestring[14] == 'N');
  assert(printablestring[15] == 'E');

  return 0;
}
