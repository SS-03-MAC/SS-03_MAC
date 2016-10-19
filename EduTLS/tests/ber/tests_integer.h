#include "../../src/encoding/ber/integer.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_ber_unsigned_integer() {
  for (uint32_t input = 0; input < 1048576; input++) {
    uint8_t encoded[11];
    uint64_t output;
    encode_int(encoded, (uint64_t)input);
    decode_int(&output, encoded);

    assert(output == (uint64_t)input);
  }

  return 0;
}

int test_ber_signed_integer() {
  for (int32_t input = -1048576; input < 1048576; input++) {
    uint8_t encoded[11];
    int64_t output;
    encode_int(encoded, (int64_t)input);
    decode_int(&output, encoded);

    assert(output == (int64_t)input);
  }

  return 0;
}
