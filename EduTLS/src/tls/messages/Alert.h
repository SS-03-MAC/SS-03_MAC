//===-- EduTLS/src/tls/messages/Alert.h                   -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Alert protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/Alert.h"
#include "../interfaces/encodable.h"

class Alert final : public encodable_i {
public:
  AlertLevel_t level;
  AlertDescription_t description;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
