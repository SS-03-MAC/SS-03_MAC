//===-- EduTLS/src/encoding/ber/bitstring.h               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains shared encoding methods for use with content type and
/// length encoding.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>

inline size_t encode_length_length(size_t length) {
  if (length < (1 << 7)) {
    return 1;
  }

  size_t result = 1;
  while (length > 0) {
    result += 1;
    length = length >> 8;
  }

  if (result == (1 << 8) - 1) {
    return 0;
  }

  return result;
}

inline void encode_length(uint8_t *result, size_t length) {
  if (length < (1 << 7)) {
    result[0] = (uint8_t)length;
    return;
  }

  uint8_t p = 1;
  while (length > 0) {
    result[p] = (uint8_t)length;
    p += 1;
    length = length >> 8;
  }

  result[0] = 0x80 | (p - 2);
}

inline size_t decode_length(uint8_t *length) {
  if ((length[0] & 0x80) == 0) {
    return length[0];
  }

  if ((length[0] & 0x7F) > 8) {
    return 0;
  }

  size_t result = 0;
  for (int p = 0; p < (length[0] & 0x7F); p++) {
    result = result << 8;
    result = result | length[p];
  }

  return result;
}
