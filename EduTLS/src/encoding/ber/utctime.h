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
#include "../time.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

inline void encode_utctime(uint8_t *result, struct UTCTime *t) {
  result[0] = BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_UTC_TIME_CLASS;
  result[1] = 13;
  result[2] = '0' + ((t->year / 10) % 10);
  result[3] = '0' + (t->year % 10);
  result[4] = '0' + ((t->month / 10) % 10);
  result[5] = '0' + (t->month % 10);
  result[6] = '0' + ((t->day / 10) % 10);
  result[7] = '0' + (t->day % 10);
  result[8] = '0' + ((t->hour / 10) % 10);
  result[9] = '0' + (t->hour % 10);
  result[10] = '0' + ((t->minute / 10) % 10);
  result[11] = '0' + (t->minute % 10);
  result[12] = '0' + ((t->second / 10) % 10);
  result[13] = '0' + (t->second % 10);
  result[14] = 'Z';
}

inline size_t encode_utctime_length() { return 15; }

inline void decode_utctime(struct UTCTime *t, uint8_t *encoded) {
  size_t i = 2;

  if (encoded[0] != (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_UTC_TIME_CLASS)) {
    return;
  }

  if (encoded[1] != 13) {
    return;
  }

  if (encoded[14] != 'Z') {
    return;
  }

  for (i = 2; i < 14; i++) {
    if ((encoded[i] - '0') < 0 || (encoded[i] - '0') > 9) {
      return;
    }
  }

  t->year = (encoded[2] - '0') * 10 + (encoded[3] - '0');
  t->month = (encoded[4] - '0') * 10 + (encoded[5] - '0');
  t->day = (encoded[6] - '0') * 10 + (encoded[7] - '0');

  t->hour = (encoded[8] - '0') * 10 + (encoded[9] - '0');
  t->minute = (encoded[10] - '0') * 10 + (encoded[11] - '0');
  t->second = (encoded[12] - '0') * 10 + (encoded[13] - '0');
}
