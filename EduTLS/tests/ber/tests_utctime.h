#include "../../src/encoding/ber/utctime.h"
#include "../../src/encoding/time.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_utctime_encode() {
  struct UTCTime t;
  uint8_t result[15];

  t.year = 16;
  t.month = 10;
  t.day = 18;

  t.hour = 8;
  t.minute = 27;
  t.second = 2;

  encode_utctime(result, &t);

  assert(result[0] == 0x17);
  assert(result[1] == 13);
  assert(result[2] == '1');
  assert(result[3] == '6');
  assert(result[4] == '1');
  assert(result[5] == '0');
  assert(result[6] == '1');
  assert(result[7] == '8');
  assert(result[8] == '0');
  assert(result[9] == '8');
  assert(result[10] == '2');
  assert(result[11] == '7');
  assert(result[12] == '0');
  assert(result[13] == '2');
  assert(result[14] == 'Z');

  return 0;
}

int test_ber_utctime_decode() {
  struct UTCTime t;
  uint8_t encoded[15] = {0x17, 13, '1', '6', '1', '0', '1', '8', '0', '8', '2', '7', '0', '2', 'Z'};

  decode_utctime(&t, encoded);

  assert(t.year == 16);
  assert(t.month == 10);
  assert(t.day == 18);

  assert(t.hour == 8);
  assert(t.minute == 27);
  assert(t.second == 2);

  return 0;
}
