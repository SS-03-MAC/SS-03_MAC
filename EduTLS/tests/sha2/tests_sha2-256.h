#include "../../src/crypto/hash/sha2-256.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_sha2_256_null() {
  sha2_256 m;

  uint8_t expected[32] = {0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4,
                          0xc8, 0x99, 0x6f, 0xb9, 0x24, 0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b,
                          0x93, 0x4c, 0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55};
  uint8_t actual[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  m.init();
  m.update(expected, 0);
  m.finalize(actual);

  for (int i = 0; i < 32; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_256_foxdog() {
  sha2_256 m;

  uint8_t expected[32] = {0xd7, 0xa8, 0xfb, 0xb3, 0x07, 0xd7, 0x80, 0x94, 0x69, 0xca, 0x9a,
                          0xbc, 0xb0, 0x08, 0x2e, 0x4f, 0x8d, 0x56, 0x51, 0xe4, 0x6d, 0x3c,
                          0xdb, 0x76, 0x2d, 0x02, 0xd0, 0xbf, 0x37, 0xc9, 0xe5, 0x92};
  uint8_t actual[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[44] = "The quick brown fox jumps over the lazy dog";

  m.init();
  m.update((uint8_t *)input, 43);
  m.finalize(actual);

  for (int i = 0; i < 32; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}

int test_sha2_256_foxdog_period() {
  sha2_256 m;

  uint8_t expected[32] = {0xef, 0x53, 0x7f, 0x25, 0xc8, 0x95, 0xbf, 0xa7, 0x82, 0x52, 0x65,
                          0x29, 0xa9, 0xb6, 0x3d, 0x97, 0xaa, 0x63, 0x15, 0x64, 0xd5, 0xd7,
                          0x89, 0xc2, 0xb7, 0x65, 0x44, 0x8c, 0x86, 0x35, 0xfb, 0x6c};
  uint8_t actual[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  unsigned char input[45] = "The quick brown fox jumps over the lazy dog.";

  m.init();
  m.update((uint8_t *)input, 44);
  m.finalize(actual);

  for (int i = 0; i < 32; i++) {
    assert(actual[i] == expected[i]);
  }

  return 0;
}
