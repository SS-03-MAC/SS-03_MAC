//===-- EduTLS/src/encoding/ber/bitstring.h               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for bitstring types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../constants/asn1.h"
#include "../constants/ber.h"
#include "shared.h"

#include <cstddef>
#include <cstdint>

inline void encode_bitstring(uint8_t *result, uint8_t *value, size_t length) {
  int offset = encode_length_length(length);
  if (offset == 0 && length != 0) {
    return;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BIT_STRING_CLASS;

  result++;
  encode_length(result, length);
  result--;

  for (size_t i = 0; i < length; i++) {
    result[offset + 1 + i] = value[i];
  }
}

inline size_t encode_bitstring_length(size_t length) {
  size_t result = 1;
  result += encode_length_length(length);
  result += length;

  return result;
}

inline size_t decode_bitstring_length(uint8_t *encoded) {
  encoded++;
  size_t result = decode_length(encoded);
  encoded--;
  return result;
}

inline void decode_bitstring(uint8_t *result, uint8_t *encoded, size_t length) {
  if (encoded[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BIT_STRING_CLASS)) {
    return;
  }

  if ((encoded[1] & 0x80) == 0 && length - 2 != (encoded[1] & 0x7F)) {
    return;
  }

  encoded++;
  size_t data_length = decode_length(encoded);
  encoded--;

  if (data_length == 0) {
    return;
  }

  if (data_length != length - 2) {
    return;
  }

  for (size_t p = 0; p < data_length; p++) {
    result[p] = encoded[p + 2];
  }
}
