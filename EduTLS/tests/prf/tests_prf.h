#include "../../src/crypto/crypto.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_prf_sha256() {
  uint8_t secret[16] = {0x9b, 0xbe, 0x43, 0x6b, 0xa9, 0x40, 0xf0, 0x17, 0xb1, 0x76, 0x52, 0x84, 0x9a, 0x71, 0xdb, 0x35};
  uint8_t seed[16] = {0xa0, 0xba, 0x9f, 0x93, 0x6c, 0xda, 0x31, 0x18, 0x27, 0xa6, 0xf7, 0x96, 0xff, 0xd5, 0x19, 0x8c};
  uint8_t label[10] = {0x74, 0x65, 0x73, 0x74, 0x20, 0x6c, 0x61, 0x62, 0x65, 0x6c};
  uint8_t expected[100] = {0xe3, 0xf2, 0x29, 0xba, 0x72, 0x7b, 0xe1, 0x7b, 0x8d, 0x12, 0x26, 0x20, 0x55, 0x7c, 0xd4,
                           0x53, 0xc2, 0xaa, 0xb2, 0x1d, 0x07, 0xc3, 0xd4, 0x95, 0x32, 0x9b, 0x52, 0xd4, 0xe6, 0x1e,
                           0xdb, 0x5a, 0x6b, 0x30, 0x17, 0x91, 0xe9, 0x0d, 0x35, 0xc9, 0xc9, 0xa4, 0x6b, 0x4e, 0x14,
                           0xba, 0xf9, 0xaf, 0x0f, 0xa0, 0x22, 0xf7, 0x07, 0x7d, 0xef, 0x17, 0xab, 0xfd, 0x37, 0x97,
                           0xc0, 0x56, 0x4b, 0xab, 0x4f, 0xbc, 0x91, 0x66, 0x6e, 0x9d, 0xef, 0x9b, 0x97, 0xfc, 0xe3,
                           0x4f, 0x79, 0x67, 0x89, 0xba, 0xa4, 0x80, 0x82, 0xd1, 0x22, 0xee, 0x42, 0xc5, 0xa7, 0x2e,
                           0x5a, 0x51, 0x10, 0xff, 0xf7, 0x01, 0x87, 0x34, 0x7b, 0x66};
  uint8_t actual[100];
  uint8_t input[26];
  size_t i = 0;
  for (i = 0; i < 10; i++) {
    input[i] = label[i];
  }
  for (i = 0; i < 16; i++) {
    input[10 + i] = seed[i];
  }

  prf_sha256 *prf = new prf_sha256(secret, 16, input, 26);

  prf->generate(actual, 100);

  for (i = 0; i < 100; i++) {
    assert(expected[i] == actual[i]);
  }

  return 0;
}
