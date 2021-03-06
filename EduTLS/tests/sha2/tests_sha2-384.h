#include "../../src/crypto/hash/sha2-384.h"
#include "../../src/crypto/utils.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_sha2_384_null() {
  sha2_384 m;

  uint8_t expected[48] = {0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38, 0x4c, 0xd9, 0x32, 0x7e,
                          0xb1, 0xb1, 0xe3, 0x6a, 0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43,
                          0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda, 0x27, 0x4e, 0xde, 0xbf,
                          0xe7, 0x6f, 0x65, 0xfb, 0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b};
  uint8_t actual[48] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  m.init();
  m.update(expected, 0);
  m.finalize(actual);

  for (int i = 0; i < 48; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_384_foxdog() {
  sha2_384 m;

  uint8_t expected[48] = {0xca, 0x73, 0x7f, 0x10, 0x14, 0xa4, 0x8f, 0x4c, 0x0b, 0x6d, 0xd4, 0x3c,
                          0xb1, 0x77, 0xb0, 0xaf, 0xd9, 0xe5, 0x16, 0x93, 0x67, 0x54, 0x4c, 0x49,
                          0x40, 0x11, 0xe3, 0x31, 0x7d, 0xbf, 0x9a, 0x50, 0x9c, 0xb1, 0xe5, 0xdc,
                          0x1e, 0x85, 0xa9, 0x41, 0xbb, 0xee, 0x3d, 0x7f, 0x2a, 0xfb, 0xc9, 0xb1};
  uint8_t actual[48] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[44] = "The quick brown fox jumps over the lazy dog";

  m.init();
  m.update((uint8_t *)input, 43);
  m.finalize(actual);

  for (int i = 0; i < 48; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_384_foxdog_period() {
  sha2_384 m;

  uint8_t expected[48] = {0xed, 0x89, 0x24, 0x81, 0xd8, 0x27, 0x2c, 0xa6, 0xdf, 0x37, 0x0b, 0xf7,
                          0x06, 0xe4, 0xd7, 0xbc, 0x1b, 0x57, 0x39, 0xfa, 0x21, 0x77, 0xaa, 0xe6,
                          0xc5, 0x0e, 0x94, 0x66, 0x78, 0x71, 0x8f, 0xc6, 0x7a, 0x7a, 0xf2, 0x81,
                          0x9a, 0x02, 0x1c, 0x2f, 0xc3, 0x4e, 0x91, 0xbd, 0xb6, 0x34, 0x09, 0xd7};
  uint8_t actual[48] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[45] = "The quick brown fox jumps over the lazy dog.";

  m.init();
  m.update((uint8_t *)input, 44);
  m.finalize(actual);

  for (int i = 0; i < 48; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}
