#include "../../src/crypto/symmetric/aes.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_aes128_key_expansion() {
  aes *a;
  uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  uint32_t expected[44] = {
      0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x9cf4f3c,  0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605, 0xf2c295f2,
      0x7a96b943, 0x5935807a, 0x7359f67f, 0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b, 0xef44a541, 0xa8525b7f,
      0xb671253b, 0xdb0bad00, 0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc, 0x6d88a37a, 0x110b3efd, 0xdbf98641,
      0xca0093fd, 0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f, 0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
      0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e, 0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6};

  a = aes::aes_128(key);
  uint32_t *actual = a->__testing_copy_key();

  for (size_t i = 0; i < 44; i++) {
    assert(actual[i] == expected[i]);
  }

  delete[] actual;
  delete a;

  return 0;
}

int test_aes128_encrypt() {
  aes *a;
  uint8_t plaintext[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  uint8_t ciphertext[16] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
                            0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
  uint8_t output[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

  a = aes::aes_128(key);

  a->encrypt(output, plaintext, 16);

  for (size_t i = 0; i < 16; i++) {
    assert(output[i] == ciphertext[i]);
  }

  delete a;

  return 0;
}

int test_aes128_decrypt() {
  aes *a;
  uint8_t plaintext[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  uint8_t ciphertext[16] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
                            0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
  uint8_t output[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

  a = aes::aes_128(key);

  a->decrypt(output, ciphertext, 16);

  for (size_t i = 0; i < 16; i++) {
    assert(output[i] == plaintext[i]);
  }

  delete a;

  return 0;
}

int test_aes128_avs_gfsbox() {
  aes *a;

  uint8_t plaintext[7][16] = {
      {0xf3, 0x44, 0x81, 0xec, 0x3c, 0xc6, 0x27, 0xba, 0xcd, 0x5d, 0xc3, 0xfb, 0x08, 0xf2, 0x73, 0xe6},
      {0x97, 0x98, 0xc4, 0x64, 0x0b, 0xad, 0x75, 0xc7, 0xc3, 0x22, 0x7d, 0xb9, 0x10, 0x17, 0x4e, 0x72},
      {0x96, 0xab, 0x5c, 0x2f, 0xf6, 0x12, 0xd9, 0xdf, 0xaa, 0xe8, 0xc3, 0x1f, 0x30, 0xc4, 0x21, 0x68},
      {0x6a, 0x11, 0x8a, 0x87, 0x45, 0x19, 0xe6, 0x4e, 0x99, 0x63, 0x79, 0x8a, 0x50, 0x3f, 0x1d, 0x35},
      {0xcb, 0x9f, 0xce, 0xec, 0x81, 0x28, 0x6c, 0xa3, 0xe9, 0x89, 0xbd, 0x97, 0x9b, 0x0c, 0xb2, 0x84},
      {0xb2, 0x6a, 0xeb, 0x18, 0x74, 0xe4, 0x7c, 0xa8, 0x35, 0x8f, 0xf2, 0x23, 0x78, 0xf0, 0x91, 0x44},
      {0x58, 0xc8, 0xe0, 0x0b, 0x26, 0x31, 0x68, 0x6d, 0x54, 0xea, 0xb8, 0x4b, 0x91, 0xf0, 0xac, 0xa1}};
  uint8_t ciphertext[7][16] = {
      {0x03, 0x36, 0x76, 0x3e, 0x96, 0x6d, 0x92, 0x59, 0x5a, 0x56, 0x7c, 0xc9, 0xce, 0x53, 0x7f, 0x5e},
      {0xa9, 0xa1, 0x63, 0x1b, 0xf4, 0x99, 0x69, 0x54, 0xeb, 0xc0, 0x93, 0x95, 0x7b, 0x23, 0x45, 0x89},
      {0xff, 0x4f, 0x83, 0x91, 0xa6, 0xa4, 0x0c, 0xa5, 0xb2, 0x5d, 0x23, 0xbe, 0xdd, 0x44, 0xa5, 0x97},
      {0xdc, 0x43, 0xbe, 0x40, 0xbe, 0x0e, 0x53, 0x71, 0x2f, 0x7e, 0x2b, 0xf5, 0xca, 0x70, 0x72, 0x09},
      {0x92, 0xbe, 0xed, 0xab, 0x18, 0x95, 0xa9, 0x4f, 0xaa, 0x69, 0xb6, 0x32, 0xe5, 0xcc, 0x47, 0xce},
      {0x45, 0x92, 0x64, 0xf4, 0x79, 0x8f, 0x6a, 0x78, 0xba, 0xcb, 0x89, 0xc1, 0x5e, 0xd3, 0xd6, 0x01},
      {0x08, 0xa4, 0xe2, 0xef, 0xec, 0x8a, 0x8e, 0x33, 0x12, 0xca, 0x74, 0x60, 0xb9, 0x04, 0x0b, 0xbf},
  };
  uint8_t output[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t key[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  a = aes::aes_128(key);

  for (size_t j = 0; j < 7; j++) {
    a->encrypt(output, plaintext[j], 16);

    for (size_t i = 0; i < 16; i++) {
      assert(output[i] == ciphertext[j][i]);
    }

    a->decrypt(output, ciphertext[j], 16);

    for (size_t i = 0; i < 16; i++) {
      assert(output[i] == plaintext[j][i]);
    }
  }

  delete a;

  return 0;
}

int test_aes128_avs_keysbox() {
  aes *a;

  uint8_t plaintext[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t ciphertext[21][16] = {
      {0x6d, 0x25, 0x1e, 0x69, 0x44, 0xb0, 0x51, 0xe0, 0x4e, 0xaa, 0x6f, 0xb4, 0xdb, 0xf7, 0x84, 0x65},
      {0x6e, 0x29, 0x20, 0x11, 0x90, 0x15, 0x2d, 0xf4, 0xee, 0x05, 0x81, 0x39, 0xde, 0xf6, 0x10, 0xbb},
      {0xc3, 0xb4, 0x4b, 0x95, 0xd9, 0xd2, 0xf2, 0x56, 0x70, 0xee, 0xe9, 0xa0, 0xde, 0x09, 0x9f, 0xa3},
      {0x5d, 0x9b, 0x05, 0x57, 0x8f, 0xc9, 0x44, 0xb3, 0xcf, 0x1c, 0xcf, 0x0e, 0x74, 0x6c, 0xd5, 0x81},
      {0xf7, 0xef, 0xc8, 0x9d, 0x5d, 0xba, 0x57, 0x81, 0x04, 0x01, 0x6c, 0xe5, 0xad, 0x65, 0x9c, 0x05},
      {0x03, 0x06, 0x19, 0x4f, 0x66, 0x6d, 0x18, 0x36, 0x24, 0xaa, 0x23, 0x0a, 0x8b, 0x26, 0x4a, 0xe7},
      {0x85, 0x80, 0x75, 0xd5, 0x36, 0xd7, 0x9c, 0xce, 0xe5, 0x71, 0xf7, 0xd7, 0x20, 0x4b, 0x1f, 0x67},
      {0x35, 0x87, 0x0c, 0x6a, 0x57, 0xe9, 0xe9, 0x23, 0x14, 0xbc, 0xb8, 0x08, 0x7c, 0xde, 0x72, 0xce},
      {0x6c, 0x68, 0xe9, 0xbe, 0x5e, 0xc4, 0x1e, 0x22, 0xc8, 0x25, 0xb7, 0xc7, 0xaf, 0xfb, 0x43, 0x63},
      {0xf5, 0xdf, 0x39, 0x99, 0x0f, 0xc6, 0x88, 0xf1, 0xb0, 0x72, 0x24, 0xcc, 0x03, 0xe8, 0x6c, 0xea},
      {0xbb, 0xa0, 0x71, 0xbc, 0xb4, 0x70, 0xf8, 0xf6, 0x58, 0x6e, 0x5d, 0x3a, 0xdd, 0x18, 0xbc, 0x66},
      {0x43, 0xc9, 0xf7, 0xe6, 0x2f, 0x5d, 0x28, 0x8b, 0xb2, 0x7a, 0xa4, 0x0e, 0xf8, 0xfe, 0x1e, 0xa8},
      {0x35, 0x80, 0xd1, 0x9c, 0xff, 0x44, 0xf1, 0x01, 0x4a, 0x7c, 0x96, 0x6a, 0x69, 0x05, 0x9d, 0xe5},
      {0x80, 0x6d, 0xa8, 0x64, 0xdd, 0x29, 0xd4, 0x8d, 0xea, 0xfb, 0xe7, 0x64, 0xf8, 0x20, 0x2a, 0xef},
      {0xa3, 0x03, 0xd9, 0x40, 0xde, 0xd8, 0xf0, 0xba, 0xff, 0x6f, 0x75, 0x41, 0x4c, 0xac, 0x52, 0x43},
      {0xc2, 0xda, 0xbd, 0x11, 0x7f, 0x8a, 0x3e, 0xca, 0xbf, 0xbb, 0x11, 0xd1, 0x21, 0x94, 0xd9, 0xd0},
      {0xff, 0xf6, 0x0a, 0x47, 0x40, 0x08, 0x6b, 0x3b, 0x9c, 0x56, 0x19, 0x5b, 0x98, 0xd9, 0x1a, 0x7b},
      {0x81, 0x46, 0xa0, 0x8e, 0x23, 0x57, 0xf0, 0xca, 0xa3, 0x0c, 0xa8, 0xc9, 0x4d, 0x1a, 0x05, 0x44},
      {0x4b, 0x98, 0xe0, 0x6d, 0x35, 0x6d, 0xeb, 0x07, 0xeb, 0xb8, 0x24, 0xe5, 0x71, 0x3f, 0x7b, 0xe3},
      {0x7a, 0x20, 0xa5, 0x3d, 0x46, 0x0f, 0xc9, 0xce, 0x04, 0x23, 0xa7, 0xa0, 0x76, 0x4c, 0x6c, 0xf2},
      {0xf4, 0xa7, 0x0d, 0x8a, 0xf8, 0x77, 0xf9, 0xb0, 0x2b, 0x4c, 0x40, 0xdf, 0x57, 0xd4, 0x5b, 0x17}};

  uint8_t output[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t key[21]
             [16] = {{0x10, 0xa5, 0x88, 0x69, 0xd7, 0x4b, 0xe5, 0xa3, 0x74, 0xcf, 0x86, 0x7c, 0xfb, 0x47, 0x38, 0x59},
                     {0xca, 0xea, 0x65, 0xcd, 0xbb, 0x75, 0xe9, 0x16, 0x9e, 0xcd, 0x22, 0xeb, 0xe6, 0xe5, 0x46, 0x75},
                     {0xa2, 0xe2, 0xfa, 0x9b, 0xaf, 0x7d, 0x20, 0x82, 0x2c, 0xa9, 0xf0, 0x54, 0x2f, 0x76, 0x4a, 0x41},
                     {0xb6, 0x36, 0x4a, 0xc4, 0xe1, 0xde, 0x1e, 0x28, 0x5e, 0xaf, 0x14, 0x4a, 0x24, 0x15, 0xf7, 0xa0},
                     {0x64, 0xcf, 0x9c, 0x7a, 0xbc, 0x50, 0xb8, 0x88, 0xaf, 0x65, 0xf4, 0x9d, 0x52, 0x19, 0x44, 0xb2},
                     {0x47, 0xd6, 0x74, 0x2e, 0xef, 0xcc, 0x04, 0x65, 0xdc, 0x96, 0x35, 0x5e, 0x85, 0x1b, 0x64, 0xd9},
                     {0x3e, 0xb3, 0x97, 0x90, 0x67, 0x8c, 0x56, 0xbe, 0xe3, 0x4b, 0xbc, 0xde, 0xcc, 0xf6, 0xcd, 0xb5},
                     {0x64, 0x11, 0x0a, 0x92, 0x4f, 0x07, 0x43, 0xd5, 0x00, 0xcc, 0xad, 0xae, 0x72, 0xc1, 0x34, 0x27},
                     {0x18, 0xd8, 0x12, 0x65, 0x16, 0xf8, 0xa1, 0x2a, 0xb1, 0xa3, 0x6d, 0x9f, 0x04, 0xd6, 0x8e, 0x51},
                     {0xf5, 0x30, 0x35, 0x79, 0x68, 0x57, 0x84, 0x80, 0xb3, 0x98, 0xa3, 0xc2, 0x51, 0xcd, 0x10, 0x93},
                     {0xda, 0x84, 0x36, 0x7f, 0x32, 0x5d, 0x42, 0xd6, 0x01, 0xb4, 0x32, 0x69, 0x64, 0x80, 0x2e, 0x8e},
                     {0xe3, 0x7b, 0x1c, 0x6a, 0xa2, 0x84, 0x6f, 0x6f, 0xdb, 0x41, 0x3f, 0x23, 0x8b, 0x08, 0x9f, 0x23},
                     {0x6c, 0x00, 0x2b, 0x68, 0x24, 0x83, 0xe0, 0xca, 0xbc, 0xc7, 0x31, 0xc2, 0x53, 0xbe, 0x56, 0x74},
                     {0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55, 0xab, 0xa9, 0x61, 0x10, 0xab, 0x58, 0x89, 0x3a, 0x8a, 0xe1},
                     {0xb6, 0x94, 0x18, 0xa8, 0x53, 0x32, 0x24, 0x0d, 0xc8, 0x24, 0x92, 0x35, 0x39, 0x56, 0xae, 0x0c},
                     {0x71, 0xb5, 0xc0, 0x8a, 0x19, 0x93, 0xe1, 0x36, 0x2e, 0x4d, 0x0c, 0xe9, 0xb2, 0x2b, 0x78, 0xd5},
                     {0xe2, 0x34, 0xcd, 0xca, 0x26, 0x06, 0xb8, 0x1f, 0x29, 0x40, 0x8d, 0x5f, 0x6d, 0xa2, 0x12, 0x06},
                     {0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a, 0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82, 0x8b, 0xb7, 0x8c, 0x6f},
                     {0x30, 0x71, 0xa2, 0xa4, 0x8f, 0xe6, 0xcb, 0xd0, 0x4f, 0x1a, 0x12, 0x90, 0x98, 0xe3, 0x08, 0xf8},
                     {0x90, 0xf4, 0x2e, 0xc0, 0xf6, 0x83, 0x85, 0xf2, 0xff, 0xc5, 0xdf, 0xc0, 0x3a, 0x65, 0x4d, 0xce},
                     {0xfe, 0xbd, 0x9a, 0x24, 0xd8, 0xb6, 0x5c, 0x1c, 0x78, 0x7d, 0x50, 0xa4, 0xed, 0x36, 0x19, 0xa9}};

  for (size_t j = 0; j < 21; j++) {
    a = aes::aes_128(key[j]);

    a->encrypt(output, plaintext, 16);

    for (size_t i = 0; i < 16; i++) {
      assert(output[i] == ciphertext[j][i]);
    }

    a->decrypt(output, ciphertext[j], 16);

    for (size_t i = 0; i < 16; i++) {
      assert(output[i] == plaintext[i]);
    }

    delete a;
  }

  return 0;
}