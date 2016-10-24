//===-- EduTLS/src/tls/messages/ProtocolVersion.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Protocol Version protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"

class ProtocolVersion_t final : public encodable_i {
public:
  uint8_t major;
  uint8_t minor;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
