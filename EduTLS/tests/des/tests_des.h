#include "../../src/crypto/symmetric/des.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_des_encrypt() {
  uint8_t plaintext[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t ciphertext[8] = {0x95, 0xA8, 0xD7, 0x28, 0x13, 0xDA, 0xA9, 0x4D};
  uint8_t output[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint64_t key = 0x8000000000000000ull;
  des *a = new des(key);

  a->encrypt(output, plaintext, 8);

  for (size_t i = 0; i < 8; i++) {
    assert(output[i] == ciphertext[i]);
  }

  delete a;

  return 0;
}

int test_des_decrypt() {
  uint8_t plaintext[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t ciphertext[8] = {0x95, 0xA8, 0xD7, 0x28, 0x13, 0xDA, 0xA9, 0x4D};
  uint8_t output[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint64_t key = 0x8000000000000000ull;
  des *a = new des(key);

  a->decrypt(output, ciphertext, 8);

  for (size_t i = 0; i < 8; i++) {
    assert(output[i] == plaintext[i]);
  }

  delete a;

  return 0;
}
