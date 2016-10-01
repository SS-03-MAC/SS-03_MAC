//===-- EduTLS/src/crypto/padding.h                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains common utility methods for padding messages under various
/// standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>

static inline size_t edutls_pad_pkcs7_size(size_t input_length, size_t pad_length) {
  return ((input_length / pad_length) + 1) * pad_length;
}

static inline void edutls_pad_pkcs7(uint8_t *output, uint8_t *input, size_t input_length, size_t pad_length) {
  size_t i = 0;
  uint8_t pad_character = (uint8_t)(pad_length - (input_length % pad_length));

  for (i = 0; i < input_length; i++) {
    output[i] = input[i];
  }

  for (; i < edutls_pad_pkcs7_size(input_length, pad_length); i++) {
    output[i] = pad_character;
  }
}

static inline bool edutls_unpad_pkcs7(uint8_t *output, uint8_t *input, size_t input_length, size_t pad_length) {
  size_t i = 0;
  uint8_t pad_character = input[input_length - 1];
  bool valid_padding = pad_character <= pad_length;

  for (i = 0; i < input_length - pad_character; i++) {
    output[i] = input[i];
  }

  for (; i < input_length; i++) {
    valid_padding = valid_padding && (input[i] == pad_character);
  }

  return valid_padding;
}
