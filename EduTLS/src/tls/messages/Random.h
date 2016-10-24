//===-- EduTLS/src/tls/messages/Random.h                  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Random protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"

class Random_t final : public encodable_i {
public:
  uint32_t gmt_unix_time;
  uint8_t random_bytes[28];

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
