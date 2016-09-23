//===-- EduTLS/src/crypto/symmetric/aes.cpp               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the AES class core methods.
///
//===----------------------------------------------------------------------===//

#include "aes.h"
#include "../constants/aes.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>

aes::aes(uint8_t *key, size_t size) {
  size_t block;
  uint32_t temp;

  this->block_size = 128;
  this->key_size = size / 4;
  this->rounds = 12 + ((int)(size - 24)) / 4;

  this->key = new uint32_t[4 * (this->rounds + 1)];

  // Loop unrolled, switch variant of Figure 11
  switch (size) {
  case 32:
    this->key[7] = (key[28] << 24) + (key[29] << 16) + (key[30] << 8) + (key[31] << 0);
    this->key[6] = (key[24] << 24) + (key[25] << 16) + (key[26] << 8) + (key[27] << 0);
  case 24:
    this->key[5] = (key[20] << 24) + (key[21] << 16) + (key[22] << 8) + (key[23] << 0);
    this->key[4] = (key[16] << 24) + (key[17] << 16) + (key[18] << 8) + (key[19] << 0);
  case 16:
    this->key[3] = (key[12] << 24) + (key[13] << 16) + (key[14] << 8) + (key[15] << 0);
    this->key[2] = (key[8] << 24) + (key[9] << 16) + (key[10] << 8) + (key[11] << 0);
    this->key[1] = (key[4] << 24) + (key[5] << 16) + (key[6] << 8) + (key[7] << 0);
    this->key[0] = (key[0] << 24) + (key[1] << 16) + (key[2] << 8) + (key[3] << 0);
    break;
  default:
    throw new std::invalid_argument("Invalid key_size for AES.");
  }

  for (block = this->key_size; block < 4 * (this->rounds + 1); block++) {
    temp = this->key[block - 1];

    if ((block % this->key_size) == 0) {
      temp = this->sub_word(edutls_rotl32(temp, 8)) ^ edutls_aes_round_constants[block / this->key_size];
    } else if (this->key_size == 8 && (block % this->key_size) == 4) {
      temp = this->sub_word(temp);
    }

    this->key[block] = this->key[block - this->key_size] ^ temp;
  }
}

aes::~aes() { delete[] this->key; }

aes *aes::aes_128(uint8_t key[16]) { return new aes(key, 16); }

aes *aes::aes_192(uint8_t key[24]) { return new aes(key, 24); }

aes *aes::aes_256(uint8_t key[32]) { return new aes(key, 32); }

int aes::encrypt(uint8_t *output, uint8_t *input, size_t count) {
  size_t i = 0;

  if (count * 8 != block_size) {
    return 1;
  }

  this->map(this->block, input);

  this->add_round_key(0);

  for (i = 1; i < this->rounds; i++) {
    this->sub_bytes();
    this->shift_rows();
    this->mix_columns();
    this->add_round_key(i);
  }

  this->sub_bytes();
  this->shift_rows();
  this->add_round_key(this->rounds);

  this->map(output, this->block);

  return 0;
}

int aes::decrypt(uint8_t *output, uint8_t *input, size_t count) {
  size_t i = 0;

  if (count * 8 != block_size) {
    return 1;
  }

  this->map(this->block, input);

  this->add_round_key(this->rounds);

  for (i = this->rounds - 1; i > 0; i--) {
    this->inverse_shift_rows();
    this->inverse_sub_bytes();
    this->add_round_key(i);
    this->inverse_mix_columns();
  }

  this->inverse_shift_rows();
  this->inverse_sub_bytes();
  this->add_round_key(0);

  this->map(output, this->block);

  return 0;
}
