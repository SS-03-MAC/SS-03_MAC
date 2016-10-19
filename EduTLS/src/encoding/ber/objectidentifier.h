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

  size_t p = 0;
  while (value > 0) {
    result[p] = value & 0x7F;
    p += 1;
    value = value >> 7;
  }
  return p;
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

  size_t result = encode_objectidentifier_subidentifier_length(40 * value[0] + value[1]);

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

  size_t size = encode_objectidentifier_length(value, length);

  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OBJECT_IDENTIFIER_CLASS;
  encode_length(&(result[1]), size);

  size_t offset = encode_objectidentifier_subidentifier(&(result[2]), 40 * value[0] + value[1]);
  for (size_t i = 2; i < length; i++) {
    encode_objectidentifier_subidentifier(&(result[2 + offset]), value[i]);
  }
}
