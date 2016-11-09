//===-- EduTLS/src/encoding/ber/objectidentifier.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for objectidentifier types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../constants/asn1.h"
#include "../constants/ber.h"
#include "shared.h"

#include <cstddef>
#include <cstdint>

inline size_t encode_objectidentifier_subidentifier(uint8_t *result, uint32_t value) {
  if (value < 0x7F) {
    result[0] = value;
    return 1;
  }

  if (value < 0x3FFF) {
    result[0] = (value >> 7) | 0x80;
    result[1] = value & 0x7F;
    return 2;
  }

  if (value < 0xFFFFFFF) {
    result[0] = ((value >> 21) & 0x7F) | 0x80;
    result[1] = ((value >> 14) & 0x7F) | 0x80;
    result[2] = ((value >> 7) & 0x7F) | 0x80;
    result[3] = value & 0x7F;
    return 4;
  }

  return 0;
}

inline size_t encode_objectidentifier_subidentifier_length(uint32_t value) {
  if (value < 0x7F) {
    return 1;
  }

  size_t result = 0;
  while (value > 0) {
    result += 1;
    value = value >> 7;
  }

  return result;
}

inline size_t encode_objectidentifier_length(uint32_t *value, size_t length) {
  if (length < 2) {
    return 0;
  }

  if (value[0] >= 3) {
    return 0;
  }

  if ((value[0] == 0 || value[0] == 1) && value[1] > 39) {
    return 0;
  }

  size_t result = 1 + encode_length_length(length);

  result += encode_objectidentifier_subidentifier_length(40 * value[0] + value[1]);

  for (size_t i = 2; i < length; i++) {
    result += encode_objectidentifier_subidentifier_length(value[i]);
  }

  return result;
}

inline void encode_objectidentifier(uint8_t *result, uint32_t *value, size_t length) {
  if (length < 2) {
    return;
  }

  if (value[0] >= 3) {
    return;
  }

  if ((value[0] == 0 || value[0] == 1) && value[1] > 39) {
    return;
  }

  size_t size = encode_objectidentifier_length(value, length) - 1 - encode_length_length(length);

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OBJECT_IDENTIFIER_CLASS;
  encode_length(&(result[1]), size);

  size_t offset = encode_objectidentifier_subidentifier(&(result[2]), 40 * value[0] + value[1]);
  for (size_t i = 2; i < length; i++) {
    encode_objectidentifier_subidentifier(&(result[2 + offset]), value[i]);
  }
}

inline uint32_t decode_objectidentifier_subidentifier(uint8_t *value, size_t length) {
  uint32_t result = 0;

  if (length == 1) {
    return value[0];
  }

  for (size_t i = 0; i < length; i++) {
    result = result << 7;
    result |= value[i] & 0x7F;
  }

  if ((value[length - 1] & 0x80) != 0) {
    return 0;
  }

  return result;
}

inline size_t decode_objectidentifier_subidentifier_length(uint8_t *value) {
  size_t result = 1;

  if (value[0] < 0x7F) {
    return result;
  }

  while ((value[result] & 0x80) == 0x80 && result < 4) {
    result += 1;
  }

  result += 1;

  return result;
}

inline size_t decode_objectidentifier_length(uint8_t *value, size_t length) {
  if (value[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OBJECT_IDENTIFIER_CLASS)) {
    return 0;
  }

  if ((value[1] & 0x80) == 0 && (length - 2) != (value[1] & 0x7F)) {
    return 0;
  }

  size_t data_length = decode_length(&(value[1]));

  size_t offset = 2;
  if ((value[1] & 0x80) == 0x80) {
    offset += value[1] & 0x7F;
  }

  if (data_length == 0) {
    return 0;
  }

  if (data_length != length - offset) {
    return 0;
  }

  size_t data_pos = 0;
  size_t result = 1;
  for (data_pos = 0; data_pos < length - offset;) {
    data_pos += decode_objectidentifier_subidentifier_length(&(value[offset + data_pos]));
    result += 1;
  }

  return result;
}

inline void decode_objectidentifier(uint32_t *result, uint8_t *value, size_t length) {
  if (value[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OBJECT_IDENTIFIER_CLASS)) {
    return;
  }

  if ((value[1] & 0x80) == 0 && (length - 2) != (value[1] & 0x7F)) {
    return;
  }

  size_t value_length = decode_length(&(value[1]));

  size_t offset = 2;
  if ((value[1] & 0x80) == 0x80) {
    offset += value[1] & 0x7F;
  }

  if (value_length == 0) {
    return;
  }

  if (value_length != length - offset) {
    return;
  }

  size_t data_pos = 0;
  size_t result_pos = 1;
  uint32_t data = 0;
  size_t data_length = 0;

  for (data_pos = 0; data_pos < value_length;) {
    data_length = decode_objectidentifier_subidentifier_length(&(value[offset + data_pos]));
    data = decode_objectidentifier_subidentifier(&(value[offset + data_pos]), data_length);

    if (result_pos == 1) {
      if (data < 40) {
        result[0] = 0;
      } else if (data < 80) {
        result[0] = 1;
        data -= 40;
      } else {
        result[0] = 2;
        data -= 80;
      }
      result[1] = data;
    } else {
      result[result_pos] = data;
    }

    data_pos += data_length;
    result_pos += 1;
  }
}
