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

#include "../../bignum/bigint.h"
#include "../constants/asn1.h"
#include "../constants/ber.h"
#include "./shared.h"

#include <cstddef>
#include <cstdint>

inline void encode_bigint(uint8_t *result, BigInt *value) {
  value->trim();

  if (value->isNegative()) {
    BigInt *max = new BigInt(1, false);
    max->left_shift(8 * value->length());
    BigInt *data = max->add(value);

    size_t length = data->length();
    uint8_t contents[length];
    size_t written = data->bytes(contents);
    size_t offset = 0;

    if (written > length) {
      delete max;
      delete data;
      return;
    }

    while (offset < length && ((contents[offset] == 0xFF && (contents[offset + 1] & 0x80) == 0x80) ||
                               (contents[offset] == 0x00 && (contents[offset + 1] & 0x80) == 0x00))) {
      offset += 1;
    }

    if ((contents[offset] & 0x80) != 0x80) {
      delete max;
      delete data;
      return;
    }

    result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS;

    encode_length(&(result[1]), written - offset);

    size_t r_offset = 1 + encode_length_length(written - offset);

    if ((result[1] & 0x80) == 0x80) {
      r_offset += result[1] & 0x7F;
    }

    for (size_t i = 0; i + offset < written; i++) {
      result[r_offset + i] = contents[offset + i];
    }

    delete max;
    delete data;
    return;
  }

  size_t length = value->length();
  uint8_t contents[length + 1];
  size_t written = value->bytes(&(contents[1]));
  size_t offset = 1;

  if (written > length) {
    return;
  }

  if ((contents[1] & 0x80) == 0x80) {
    offset = 0;
  }

  while (offset < length && contents[offset] == 0x00 && (contents[offset + 1] & 0x80) == 0x00) {
    offset += 1;
  }

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS;
  encode_length(&(result[1]), written - offset + 1);
  size_t r_offset = 1 + encode_length_length(written - offset + 1);
  if ((result[1] & 0x80) == 0x80) {
    r_offset += result[1] & 0x7F;
  }

  for (size_t i = 0; i + offset < written + 1; i++) {
    result[r_offset + i] = contents[offset + i];
  }

  return;
}

inline void decode_bigint(BigInt *result, uint8_t *encoded, size_t length) {
  if (encoded[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS)) {
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

  BigInt *data = new BigInt(false, &(encoded[offset]), length - offset);

  if ((encoded[offset] & 0x80) == 0x80) {
    BigInt *max = new BigInt(1, false);
    max->left_shift(8 * data_length);
    BigInt *tc = max->sub(data);
    result->copy(tc);

    if (!result->isNegative()) {
      result->negate();
    }

    delete max;
    delete tc;
  } else {
    result->copy(data);
  }
  delete data;
  return;
}
