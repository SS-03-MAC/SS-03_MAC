//===-- EduTLS/src/encoding/hex.h                         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding and decoding methods for hexadecimal
/// representations of bit arrays.
///
//===----------------------------------------------------------------------===//

#pragma once

const char hex_charset[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static inline void toHex(char *dest, uint8_t *src, size_t length) {
  size_t r = 0;
  size_t w = 0;

  for (; r < length; r++) {
    dest[w] = hex_charset[(src[r] >> 4)];
    w += 1;
    dest[w] = hex_charset[src[r] & 0x0F];
    w += 1;
  }
}

static inline bool fromHex(uint8_t *dest, char *src, size_t length) {
  size_t r = 0;
  size_t w = 0;

  if (length % 2 != 0) {
    int num_value = src[r] - '0';
    int lower_value = src[r] - 'a';
    int upper_value = src[r] - 'A';

    if (num_value >= 0 && num_value <= 9) {
      dest[w] = num_value;
    } else if (lower_value >= 0 && lower_value <= 5) {
      dest[w] = lower_value + 10;
    } else if (upper_value >= 0 && upper_value <= 5) {
      dest[w] = upper_value + 10;
    } else {
      return false;
    }

    w += 1;
    r += 1;
  }

  for (; r < length; r += 1) {
    int num_value = src[r] - '0';
    int lower_value = src[r] - 'a';
    int upper_value = src[r] - 'A';

    if (num_value >= 0 && num_value <= 9) {
      dest[w] = num_value << 4;
    } else if (lower_value >= 0 && lower_value <= 5) {
      dest[w] = (lower_value + 10) << 4;
    } else if (upper_value >= 0 && upper_value <= 5) {
      dest[w] = (upper_value + 10) << 4;
    } else {
      return false;
    }

    r += 1;
    num_value = src[r] - '0';
    lower_value = src[r] - 'a';
    upper_value = src[r] - 'A';

    if (num_value >= 0 && num_value <= 9) {
      dest[w] ^= num_value;
    } else if (lower_value >= 0 && lower_value <= 5) {
      dest[w] ^= lower_value + 10;
    } else if (upper_value >= 0 && upper_value <= 5) {
      dest[w] ^= upper_value + 10;
    } else {
      return false;
    }

    w += 1;
  }

  return true;
}
