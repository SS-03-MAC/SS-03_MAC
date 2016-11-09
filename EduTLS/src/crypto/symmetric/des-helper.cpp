//===-- EduTLS/src/crypto/symmetric/des-helper.cpp        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the DES class helper methods.
///
//===----------------------------------------------------------------------===//

#include "../constants/des.h"
#include "des.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

void des::choice_1_permute(uint32_t *C, uint32_t *D, uint64_t key) {
  uint64_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 56; pos++) {
    result = result << 1;
    result += (key >> (64 - edutls_des_permuted_choice_1[pos])) & 1;
  }

  *C = (uint32_t)(result >> 28) & 0xFFFFFF;
  *D = (uint32_t)result & 0xFFFFFFF;
}

void des::choice_2_permute(uint64_t *output, uint32_t C, uint32_t D) {
  uint64_t input = ((uint64_t)C << 28) ^ ((uint64_t)D);
  uint64_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 48; pos++) {
    result = result << 1;
    result += (input >> (56 - edutls_des_permuted_choice_2[pos])) & 1;
  }

  *output = result;
}

void des::initial_permute(uint32_t *left, uint32_t *right, uint64_t input) {
  uint64_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 64; pos++) {
    result = result << 1;
    result += (input >> (64 - edutls_des_initial_permutation_shifts[pos])) & 1;
  }

  *left = (uint32_t)(result >> 32);
  *right = (uint32_t)result;
}

void des::inverse_permute(uint64_t *output, uint32_t left, uint32_t right) {
  uint64_t input = ((uint64_t)left << 32) ^ ((uint64_t)right);
  uint64_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 64; pos++) {
    result = result << 1;
    result += (input >> (64 - edutls_des_inverse_permutation_shifts[pos])) & 1;
  }

  *output = result;
}

uint32_t des::permute_p(uint32_t input) {
  uint32_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 32; pos++) {
    result = result << 1;
    result += (input >> (32 - edutls_des_primitive_function_p[pos])) & 1;
  }

  return result;
}

uint64_t des::expand(uint32_t input) {
  uint64_t result = 0;
  size_t pos = 0;

  for (pos = 0; pos < 48; pos++) {
    result = result << 1;
    result += (input >> (32 - edutls_des_expand_shifts[pos])) & 1;
  }

  return result;
}

uint32_t des::f(uint32_t input, uint64_t key) {
  size_t pos = 0;
  uint64_t expanded_input = this->expand(input);
  uint32_t result = 0;

  uint8_t data;
  uint8_t col;
  uint8_t row;

  expanded_input = expanded_input ^ key;

  for (pos = 0; pos < 8; pos++) {
    result = result << 4;
    data = (uint8_t)(expanded_input >> (48 - (6 * (pos + 1)))) & 0x3f;
    col = (data & 0x1e) >> 1;
    row = ((data & 0x20) >> 4) ^ (data & 0x01);

    result += edutls_des_primitive_functions[pos][row * 16 + col];
  }

  result = this->permute_p(result);

  return result;
}
