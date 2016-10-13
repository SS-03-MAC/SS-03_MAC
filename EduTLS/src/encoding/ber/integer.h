//===-- EduTLS/src/encoding/ber/integer.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for integers types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../constants/asn1.h"
#include "../constants/ber.h"

#include <cstddef>
#include <cstdint>

inline void encode_int(uint8_t *result, int64_t value) {
  size_t r = 0;
  size_t w = 2;
  uint8_t contents[8];

  for (r = 0; r < 8; r++) {
    contents[7 - r] = (value >> r * 8) & 0xFF;
  }

  r = 0;

  while ((r < 7) && ((contents[r] == 0xFF && (contents[r + 1] & 0x80) == 0x80) ||
                     (contents[r] == 0x00 && (contents[r + 1] & 0x80) == 0x00))) {
    r += 1;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS;
  result[1] = 8 - r;

  for (; r < 8; r++) {
    result[w] = contents[r];
    w += 1;
  }
}

inline void encode_int(uint8_t *result, uint64_t value) {
  size_t r = 0;
  size_t w = 2;
  uint8_t contents[9];
  contents[0] = 0x00;
  for (r = 0; r < 8; r++) {
    contents[8 - r] = (value >> r * 8) & 0xFF;
  }

  r = 0;
  while ((r < 8) && ((contents[r] == 0xFF && (contents[r + 1] & 0x80) == 0x80) ||
                     (contents[r] == 0x00 && (contents[r + 1] & 0x80) == 0x00))) {
    r += 1;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS;
  result[1] = 9 - r;

  for (; r < 9; r++) {
    result[w] = contents[r];
    w += 1;
  }
}

inline void decode_int(uint64_t *result, uint8_t *encoding) {
  size_t r = 0;
  size_t o = 0;

  if (encoding[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS)) {
    return;
  }

  if (encoding[1] > 9) {
    return;
  } else if (encoding[1] == 9 && encoding[2] != 0) {
    return;
  }

  if (encoding[1] == 9) {
    o = 1;
  }

  *result = 0;
  for (; r < encoding[1]; r++) {
    *result = (*result) << 8;
    *result += encoding[2 + r + o];
  }
}

inline void decode_int(int64_t *result, uint8_t *encoding) {
  size_t r = 0;
  uint64_t mask = 0xFFFFFFFFFFFFFFFF;

  if (encoding[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS)) {
    return;
  }

  if (encoding[1] >= 9) {
    return;
  }

  *result = 0;
  for (; r < encoding[1]; r++) {
    mask = mask << 8;
    *result = (*result) << 8;
    *result += encoding[2 + r];
  }
  
  if ((encoding[2] & 0x80) == 0x80) {
    *result += (int64_t)mask;
  }
}
