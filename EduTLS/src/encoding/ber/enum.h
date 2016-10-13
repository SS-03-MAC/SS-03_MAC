//===-- EduTLS/src/encoding/ber/enum.h                    -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains encoding methods for enumerated types as defined by
/// ASN.1/BER encoding standards.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "integer.h"
#include "../constants/asn1.h"
#include "../constants/ber.h"

#include <cstddef>
#include <cstdint>

inline void encode_enum(uint8_t *result, int64_t value) {
  encode_int(result, value);
  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_ENUMERATED_CLASS;
}

inline void decode_int(uint64_t *result, uint8_t *encoding) {
  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_INTEGER_CLASS;
  decode_int(result, value);
}
