//===-- EduTLS/src/encoding/ber/printablestring.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for printablestring types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../constants/asn1.h"
#include "../constants/ber.h"
#include "shared.h"

#include <cstddef>
#include <cstdint>

inline void encode_printablestring(uint8_t *result, uint8_t *value, size_t length) {
  int offset = encode_length_length(length);
  if (offset == 0 && length != 0) {
    return;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_PRINTABLE_STRING_CLASS;

  encode_length(&(result[1]), length);

  for (size_t i = 0; i < length; i++) {
    if ((value[i] - 'A' >= 0 && value[i] - 'A' <= 26) || (value[i] - 'a' >= 0 && value[i] - 'a' <= 26) ||
    (value[i] - '0' >= 0 && value[i] - '0' <= 9) || (value[i] == ' ') || (value[i] == '\'') || (value[i] == '(') || (value[i] == ')') || (value[i] == '+') || (value[i] == ',') || (value[i] == '.') || (value[i] == '-') || (value[i] == '/') || (value[i] == ':') || (value[i] == '=') || (value[i] == '?')) {
      result[offset + 1 + i] = value[i];
    } else {
      return;
    }
  }
}

inline size_t encode_printablestring_length(size_t length) {
  size_t result = 1;
  result += encode_length_length(length);
  result += length;

  return result;
}

inline size_t decode_printablestring_length(uint8_t *encoded) {
  encoded++;
  size_t result = decode_length(encoded);
  encoded--;
  return result;
}

inline void decode_printablestring(uint8_t *result, uint8_t *encoded, size_t length) {
  if (encoded[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_PRINTABLE_STRING_CLASS)) {
    return;
  }

  if ((encoded[1] & 0x80) == 0 && (length - 2) != (encoded[1] & 0x7F)) {
    return;
  }

  size_t data_length = decode_length(&(encoded[1]));

  size_t offset = 2;
  if ((encoded[1] & 0x80) == 0x80) {
    offset += encoded[1] & 0x7F;
  }

  if (data_length == 0) {
    return;
  }

  if (data_length != length - offset) {
    return;
  }


  for (size_t p = 0; p < data_length; p++) {
    if ((encoded[p + offset] - 'A' >= 0 && encoded[p + offset] - 'A' <= 26) || (encoded[p + offset] - 'a' >= 0 && encoded[p + offset] - 'a' <= 26) ||
    (encoded[p + offset] - '0' >= 0 && encoded[p + offset] - '0' <= 9) || (encoded[p + offset] == ' ') || (encoded[p + offset] == '\'') || (encoded[p + offset] == '(') || (encoded[p + offset] == ')') || (encoded[p + offset] == '+') || (encoded[p + offset] == ',') || (encoded[p + offset] == '.') || (encoded[p + offset] == '-') || (encoded[p + offset] == '/') || (encoded[p + offset] == ':') || (encoded[p + offset] == '=') || (encoded[p + offset] == '?')) {
      result[p] = encoded[p + offset];
    } else {
      return;
    }
  }
}
