//===-- EduTLS/src/crypto/symmetric/aes-helper.cpp        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the AES class helper methods.
///
//===----------------------------------------------------------------------===//

#include "../constants/aes.h"
#include "aes.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

uint32_t aes::sub_word(uint32_t input) {
  return ((edutls_aes_sbox[(uint8_t)(input >> 24)]) << 24) + ((edutls_aes_sbox[(uint8_t)(input >> 16)]) << 16) +
         ((edutls_aes_sbox[(uint8_t)(input >> 8)]) << 8) + (edutls_aes_sbox[(uint8_t)(input >> 0)]);
}

void aes::add_round_key(uint8_t round) {
  size_t i = 0;
  uint8_t b[4];

  for (i = 0; i < 4; i++) {
    b[0] = (uint8_t)(this->key[(4 * round) + i] >> 24);
    b[1] = (uint8_t)(this->key[(4 * round) + i] >> 16);
    b[2] = (uint8_t)(this->key[(4 * round) + i] >> 8);
    b[3] = (uint8_t)(this->key[(4 * round) + i] >> 0);

    this->block[(0 * 4) + i] ^= b[0];
    this->block[(1 * 4) + i] ^= b[1];
    this->block[(2 * 4) + i] ^= b[2];
    this->block[(3 * 4) + i] ^= b[3];
  }
}

void aes::sub_bytes() {
  size_t i = 0;

  for (i = 0; i < 16; i++) {
    this->block[i] = edutls_aes_sbox[this->block[i]];
  }
}

void aes::shift_rows() {
  size_t i = 0;

  uint8_t copy[16];
  uint8_t map[16] = {0, 1, 2, 3, 5, 6, 7, 4, 10, 11, 8, 9, 15, 12, 13, 14};

  for (i = 0; i < 16; i++) {
    copy[i] = this->block[i];
  }

  for (i = 0; i < 16; i++) {
    this->block[i] = copy[map[i]];
  }
}

void aes::mix_columns() {
  size_t i = 0;
  for (i = 0; i < 4; i++) {
    uint8_t b[4];
    b[0] = this->block[0 * 4 + i];
    b[1] = this->block[1 * 4 + i];
    b[2] = this->block[2 * 4 + i];
    b[3] = this->block[3 * 4 + i];

    this->block[0 * 4 + i] = edutls_aes_gmul_2[b[0]] ^ edutls_aes_gmul_3[b[1]] ^ b[2] ^ b[3];
    this->block[1 * 4 + i] = b[0] ^ edutls_aes_gmul_2[b[1]] ^ edutls_aes_gmul_3[b[2]] ^ b[3];
    this->block[2 * 4 + i] = b[0] ^ b[1] ^ edutls_aes_gmul_2[b[2]] ^ edutls_aes_gmul_3[b[3]];
    this->block[3 * 4 + i] = edutls_aes_gmul_3[b[0]] ^ b[1] ^ b[2] ^ edutls_aes_gmul_2[b[3]];
  }
}

void aes::inverse_sub_bytes() {
  size_t i = 0;
  for (i = 0; i < 16; i++) {
    this->block[i] = edutls_aes_inverse_sbox[this->block[i]];
  }
}

void aes::inverse_shift_rows() {
  size_t i = 0;
  uint8_t copy[16];
  uint8_t map[16] = {0, 1, 2, 3, 7, 4, 5, 6, 10, 11, 8, 9, 13, 14, 15, 12};

  for (i = 0; i < 16; i++) {
    copy[i] = this->block[i];
  }

  for (i = 0; i < 16; i++) {
    this->block[i] = copy[map[i]];
  }
}

void aes::inverse_mix_columns() {

  size_t i = 0;
  for (i = 0; i < 4; i++) {
    uint8_t b[4];
    b[0] = this->block[0 * 4 + i];
    b[1] = this->block[1 * 4 + i];
    b[2] = this->block[2 * 4 + i];
    b[3] = this->block[3 * 4 + i];

    this->block[0 * 4 + i] =
        edutls_aes_gmul_14[b[0]] ^ edutls_aes_gmul_11[b[1]] ^ edutls_aes_gmul_13[b[2]] ^ edutls_aes_gmul_9[b[3]];
    this->block[1 * 4 + i] =
        edutls_aes_gmul_9[b[0]] ^ edutls_aes_gmul_14[b[1]] ^ edutls_aes_gmul_11[b[2]] ^ edutls_aes_gmul_13[b[3]];
    this->block[2 * 4 + i] =
        edutls_aes_gmul_13[b[0]] ^ edutls_aes_gmul_9[b[1]] ^ edutls_aes_gmul_14[b[2]] ^ edutls_aes_gmul_11[b[3]];
    this->block[3 * 4 + i] =
        edutls_aes_gmul_11[b[0]] ^ edutls_aes_gmul_13[b[1]] ^ edutls_aes_gmul_9[b[2]] ^ edutls_aes_gmul_14[b[3]];
  }
}

void aes::map(uint8_t *output, uint8_t *input) {
  size_t i = 0;
  uint8_t map[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

  for (i = 0; i < 16; i++) {
    output[i] = input[map[i]];
  }
}

uint32_t* aes::__testing_copy_key() {
  uint32_t *result = new uint32_t[4*(this->rounds+1)];
  size_t block = 0;
  for (block = 0; block < 4 * (this->rounds + 1); block++) {
    result[block] = this->key[block];
  }

  return result;
}
