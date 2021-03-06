//===-- EduTLS/src/crypto/utils.h                         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains common utility methods for use with many cryptographic
/// constructs.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>

static inline uint16_t edutls_rotl16(uint16_t input, uint8_t shift) {
  return ((input << shift) | (input >> (16 - shift)));
}

static inline uint32_t edutls_rotl28(uint32_t input, uint8_t shift) {
  return ((input << shift) | (input >> (28 - shift)));
}

static inline uint32_t edutls_rotl32(uint32_t input, uint8_t shift) {
  return ((input << shift) | (input >> (32 - shift)));
}

static inline uint64_t edutls_rotl64(uint64_t input, uint8_t shift) {
  return ((input << shift) | (input >> (64 - shift)));
}

static inline uint16_t edutls_rotr16(uint16_t input, uint8_t shift) {
  return ((input << (16 - shift)) | (input >> shift));
}

static inline uint32_t edutls_rotr28(uint32_t input, uint8_t shift) {
  return ((input << (28 - shift)) | (input >> shift));
}

static inline uint32_t edutls_rotr32(uint32_t input, uint8_t shift) {
  return ((input << (32 - shift)) | (input >> shift));
}

static inline uint64_t edutls_rotr64(uint64_t input, uint8_t shift) {
  return ((input << (64 - shift)) | (input >> shift));
}

static inline void edutls_xor(uint8_t *output, uint8_t *input, uint8_t *key, size_t input_length) {
  size_t i = 0;
  for (i = 0; i < input_length; i++) {
    output[i] = input[i] ^ key[i];
  }
}
