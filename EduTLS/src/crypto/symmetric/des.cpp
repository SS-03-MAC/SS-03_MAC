//===-- EduTLS/src/crypto/symmetric/des.cpp               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the DES class core methods.
///
//===----------------------------------------------------------------------===//

#include "des.h"
#include "../constants/des.h"
#include "../utils.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>

des::des(uint64_t key) {
  size_t n = 0;
  uint32_t C = 0;
  uint32_t D = 0;

  this->block_size = 64;

  this->choice_1_permute(&C, &D, key);

  C = edutls_rotl28(C, edutls_des_shift_sizes[0]);
  D = edutls_rotl28(D, edutls_des_shift_sizes[0]);

  for (n = 0; n < 15; n++) {
    this->choice_2_permute(&(this->skey[n]), C, D);

    C = edutls_rotl28(C, edutls_des_shift_sizes[n + 1]);
    D = edutls_rotl28(D, edutls_des_shift_sizes[n + 1]);
  }

  this->choice_2_permute(&(this->skey[15]), C, D);
}

uint64_t des::encrypt(uint64_t input) {
  uint32_t left;
  uint32_t right;
  uint32_t tmp;
  uint64_t result;
  size_t a = 0;

  this->initial_permute(&left, &right, input);

  for (a = 0; a < 16; a++) {
    tmp = right;
    right = left ^ this->f(right, this->skey[a]);
    left = tmp;
  }

  this->inverse_permute(&result, right, left);

  return result;
}

uint64_t des::decrypt(uint64_t input) {
  uint32_t left;
  uint32_t right;
  uint32_t tmp;
  uint64_t result;
  size_t a = 0;

  this->initial_permute(&left, &right, input);

  for (a = 16; a > 0; a--) {
    tmp = right;
    right = left ^ this->f(right, this->skey[a - 1]);
    left = tmp;
  }

  this->inverse_permute(&result, right, left);

  return result;
}

int des::encrypt(uint8_t *output, uint8_t *input, size_t count) {
  if (count * 8 != block_size) {
    throw new std::invalid_argument("Invalid input size for DES encryption.");
  }

  uint64_t input64 = (((uint64_t)input[0]) << 56) | (((uint64_t)input[1]) << 48) | (((uint64_t)input[2]) << 40) |
                     (((uint64_t)input[3]) << 32) | (((uint64_t)input[4]) << 24) | (((uint64_t)input[5]) << 16) |
                     (((uint64_t)input[6]) << 8) | (((uint64_t)input[7]) << 0);

  uint64_t result64 = this->encrypt(input64);

  output[0] = (uint8_t)(result64 >> 56);
  output[1] = (uint8_t)(result64 >> 48);
  output[2] = (uint8_t)(result64 >> 40);
  output[3] = (uint8_t)(result64 >> 32);
  output[4] = (uint8_t)(result64 >> 24);
  output[5] = (uint8_t)(result64 >> 16);
  output[6] = (uint8_t)(result64 >> 8);
  output[7] = (uint8_t)(result64 >> 0);

  return 0;
}

int des::decrypt(uint8_t *output, uint8_t *input, size_t count) {
  if (count * 8 != block_size) {
    throw new std::invalid_argument("Invalid input size for DES encryption.");
  }

  uint64_t input64 = (((uint64_t)input[0]) << 56) | (((uint64_t)input[1]) << 48) | (((uint64_t)input[2]) << 40) |
                     (((uint64_t)input[3]) << 32) | (((uint64_t)input[4]) << 24) | (((uint64_t)input[5]) << 16) |
                     (((uint64_t)input[6]) << 8) | (((uint64_t)input[7]) << 0);

  uint64_t result64 = this->decrypt(input64);

  output[0] = (uint8_t)(result64 >> 56);
  output[1] = (uint8_t)(result64 >> 48);
  output[2] = (uint8_t)(result64 >> 40);
  output[3] = (uint8_t)(result64 >> 32);
  output[4] = (uint8_t)(result64 >> 24);
  output[5] = (uint8_t)(result64 >> 16);
  output[6] = (uint8_t)(result64 >> 8);
  output[7] = (uint8_t)(result64 >> 0);

  return 0;
}
