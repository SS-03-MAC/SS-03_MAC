#include "../../src/crypto/hash/sha2-224.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_sha2_224_null() {
  sha2_224 m;

  uint8_t expected[28] = {0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9, 0x47, 0x61, 0x02, 0xbb, 0x28, 0x82,
                          0x34, 0xc4, 0x15, 0xa2, 0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a, 0xc5, 0xb3, 0xe4, 0x2f};
  uint8_t actual[28] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  m.init();
  m.update(expected, 0);
  m.finalize(actual);

  for (int i = 0; i < 28; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_224_foxdog() {
  sha2_224 m;

  uint8_t expected[28] = {0x73, 0x0e, 0x10, 0x9b, 0xd7, 0xa8, 0xa3, 0x2b, 0x1c, 0xb9, 0xd9, 0xa0, 0x9a, 0xa2,
                          0x32, 0x5d, 0x24, 0x30, 0x58, 0x7d, 0xdb, 0xc0, 0xc3, 0x8b, 0xad, 0x91, 0x15, 0x25};
  uint8_t actual[28] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[44] = "The quick brown fox jumps over the lazy dog";

  m.init();
  m.update((uint8_t *)input, 43);
  m.finalize(actual);

  for (int i = 0; i < 28; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_224_foxdog_period() {
  sha2_224 m;

  uint8_t expected[28] = {0x61, 0x9c, 0xba, 0x8e, 0x8e, 0x05, 0x82, 0x6e, 0x9b, 0x8c, 0x51, 0x9c, 0x0a, 0x5c,
                          0x68, 0xf4, 0xfb, 0x65, 0x3e, 0x8a, 0x3d, 0x8a, 0xa0, 0x4b, 0xb2, 0xc8, 0xcd, 0x4c};
  uint8_t actual[28] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[45] = "The quick brown fox jumps over the lazy dog.";

  m.init();
  m.update((uint8_t *)input, 44);
  m.finalize(actual);

  for (int i = 0; i < 28; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}
