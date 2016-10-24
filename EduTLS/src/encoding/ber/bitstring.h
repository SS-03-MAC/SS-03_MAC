//===-- EduTLS/src/encoding/ber/bitstring.h             -------*- C++ -*-===//
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

inline void encode_bitstring(uint8_t *result, uint8_t *value, uint8_t unused, size_t length) {
  int offset = encode_length_length(length + 1);
  if (offset == 0 && length != 0) {
    return;
  }

  if (unused > 8) {
    return;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BIT_STRING_CLASS;

  encode_length(&(result[1]), length + 1);

  result[offset + 1] = unused;

  offset += 1;

  for (size_t i = 0; i < length; i++) {
    result[offset + 1 + i] = value[i];
  }
}

inline size_t encode_bitstring_length(size_t length) {
  size_t result = 1;
  result += encode_length_length(length + 1);
  result += length + 1;

  return result;
}

inline size_t decode_bitstring_length(uint8_t *encoded) {
  size_t result = decode_length(&(encoded[1]));
  return result - 1;
}

inline uint8_t decode_bitstring(uint8_t *result, uint8_t *encoded, size_t length) {
  if (encoded[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BIT_STRING_CLASS)) {
    return -1;
  }

  if ((encoded[1] & 0x80) == 0 && (length - 2) != (encoded[1] & 0x7F)) {
    return -1;
  }

  size_t data_length = decode_length(&(encoded[1]));

  size_t offset = 2;
  if ((encoded[1] & 0x80) == 0x80) {
    offset += encoded[1] & 0x7F;
  }

  if (data_length == 0) {
    return -1;
  }

  if (data_length != length - offset) {
    return -1;
  }

  for (size_t p = 1; p < data_length; p++) {
    result[p - 1] = encoded[p + offset];
  }

  return encoded[offset];
}
