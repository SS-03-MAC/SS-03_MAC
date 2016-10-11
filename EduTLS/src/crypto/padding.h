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
#include <cstdio>

#define PKCS1_BT1 1
#define PKCS1_BT2 2

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

static inline void edutls_pad_pkcs1(uint8_t *output, size_t output_length, uint8_t *input, size_t input_length,
                                    int pad_type) {
  size_t i = 0;
  size_t i_p = 0;

  switch (pad_type) {
  case PKCS1_BT1:
    for (i = 0; i < output_length; i++) {
      output[i] = 0xFF;
    }
    break;
  case PKCS1_BT2:
    edutls_rand_bytes(output, output_length);
    for (i = 0; i < output_length; i++) {
      if (output[i] == 0) {
        output[i] = 1;
      }
    }
    break;
  default:
    throw - 1;
    break;
  }

  output[0] = 0;
  output[1] = pad_type;
  output[output_length - input_length - 1] = 0;
  i = output_length - input_length;
  for (i_p = 0; i_p < input_length && i < output_length; i_p++) {
    output[i] = input[i_p];
    i += 1;
  }
}

static inline bool edutls_unpad_pkcs1(uint8_t *output, uint8_t *input, size_t input_length) {
  bool valid_padding = true;
  size_t i = 0;
  size_t i_p = 0;

  valid_padding = valid_padding && (input[0] == 0);
  switch (input[1]) {
  case PKCS1_BT1:
    for (i = 2; i < input_length; i++) {
      if (input[i] == 0) {
        i_p = i + 1;
        break;
      }
      valid_padding = valid_padding && (input[i] == 0xff);
    }
    break;
  case PKCS1_BT2:
    for (i = 2; i < input_length; i++) {
      if (input[i] == 0) {
        i_p = i + 1;
        break;
      }
    }
    break;
  default:
    valid_padding = false;
    for (i = 2; i < input_length; i++) {
      if (input[i] == 0) {
        i_p = i + 1;
        break;
      }
    }
  }

  i = 0;
  while (i_p < input_length) {
    output[i] = input[i_p];
    i += 1;
    i_p += 1;
  }

  return valid_padding;
}
