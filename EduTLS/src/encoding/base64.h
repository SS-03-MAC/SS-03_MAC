//===-- EduTLS/src/encoding/base64.h                      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding and decoding methods for the base64
/// representations of data, per RFC 4648.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>

const char base64_standard_charset[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

const char base64_urlsafe_charset[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'};

const short base64_reverse_map[] = {62, -1, 62, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, 0,  -1,
                                    -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
                                    18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63, -1, 26, 27, 28, 29, 30, 31,
                                    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

static inline void toBase64(char *dest, uint8_t *src, size_t length) {
  if (length == 0) {
    return;
  }

  size_t i = 0;
  size_t d_p = 0;
  uint32_t data = 0;
  for (i = 0; i + 3 <= length; i += 3) {
    data = (src[i + 0] << 16) | (src[i + 1] << 8) | (src[i + 2] << 0);
    dest[d_p + 0] = base64_standard_charset[(data >> 18) & 0x3f];
    dest[d_p + 1] = base64_standard_charset[(data >> 12) & 0x3f];
    dest[d_p + 2] = base64_standard_charset[(data >> 6) & 0x3f];
    dest[d_p + 3] = base64_standard_charset[(data >> 0) & 0x3f];
    d_p += 4;
  }

  data = 0;
  if (length % 3 == 2) {
    data = (src[length - 2] << 16) | (src[length - 1] << 8);
    dest[d_p + 0] = base64_standard_charset[(data >> 18) & 0x3f];
    dest[d_p + 1] = base64_standard_charset[(data >> 12) & 0x3f];
    dest[d_p + 2] = base64_standard_charset[(data >> 6) & 0x3f];
    dest[d_p + 3] = '=';
  } else if (length % 3 == 1) {
    data = (src[length - 1] << 16);
    dest[d_p + 0] = base64_standard_charset[(data >> 18) & 0x3f];
    dest[d_p + 1] = base64_standard_charset[(data >> 12) & 0x3f];
    dest[d_p + 2] = '=';
    dest[d_p + 3] = '=';
  }
}

static inline bool fromBase64(uint8_t *dest, char *src, size_t length) {
  if (length == 0) {
    return true;
  }

  if (length % 4 == 1) {
    return false;
  }

  size_t i = 0;
  size_t d_p = 0;
  uint32_t data = 0;

  for (i = 0; i + 4 <= length; i += 4) {
    if (src[i + 0] - '+' < 0 || src[i + 0] - 'z' > 0) {
      return false;
    }
    if (src[i + 1] - '+' < 0 || src[i + 1] - 'z' > 0) {
      return false;
    }
    if (src[i + 2] - '+' < 0 || src[i + 2] - 'z' > 0) {
      return false;
    }
    if (src[i + 3] - '+' < 0 || src[i + 3] - 'z' > 0) {
      return false;
    }

    if (base64_reverse_map[src[i + 0] - '+'] < 0) {
      printf("Error decoding %c\n", src[i + 0]);
      return false;
    }
    if (base64_reverse_map[src[i + 1] - '+'] < 0) {
      printf("Error decoding %c\n", src[i + 1]);
      return false;
    }
    if (base64_reverse_map[src[i + 2] - '+'] < 0) {
      printf("Error decoding %c\n", src[i + 2]);
      return false;
    }
    if (base64_reverse_map[src[i + 3] - '+'] < 0) {
      printf("Error decoding %c\n", src[i + 3]);
      return false;
    }

    data = (base64_reverse_map[src[i + 0] - '+'] << 18) | (base64_reverse_map[src[i + 1] - '+'] << 12) |
           (base64_reverse_map[src[i + 2] - '+'] << 6) | (base64_reverse_map[src[i + 3] - '+'] << 0);

    dest[d_p + 0] = (data >> 16) & 0xFF;
    if (src[i + 2] != '=') {
      dest[d_p + 1] = (data >> 8) & 0xFF;
    }
    if (src[i + 3] != '=') {
      dest[d_p + 2] = data & 0xFF;
    }

    d_p += 3;
  }

  return true;
}
