//===-- EduTLS/src/encoding/ber/boolean.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for boolena types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../constants/ber.h"
#include "../constants/asn1.h"

#include <cstdint>
#include <cstddef>

static inline void encode_boolean(uint8_t* result, bool value) {
  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BOOLEAN_CLASS;
  result[1] = BER_VALUE_BOOLEAN_LENGTH;

  if (value) {
    result[2] = BER_VALUE_BOOLEAN_VALUE_TRUE;
  } else {
    result[2] = BER_VALUE_BOOLEAN_VALUE_FALSE;
  }
}

static inline size_t encode_boolean_length() {
  return 3;
}

static inline void decode_boolean(bool* result, uint8_t* encoding) {
  if (encoding[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BOOLEAN_CLASS)) {
    return;
  }

  if (encoding[1] != BER_VALUE_BOOLEAN_LENGTH) {
    return;
  }

  if (encoding[2] == BER_VALUE_BOOLEAN_VALUE_FALSE) {
    *result = false;
  } else {
    *result = true;
  }
}

static inline size_t decode_boolean_length() {
  return 1;
}
