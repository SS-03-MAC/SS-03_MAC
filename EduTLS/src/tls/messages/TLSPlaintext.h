//===-- EduTLS/src/tls/messages/TLSPlaintext.h            -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the TLS Plaintext protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ContentType.h"
#include "../interfaces/encodable.h"

class TLSPlaintext : public encodable_i {
public:
  ContentType_t type;
  ProtocolVersion_t version;
  uint16_t length;
  uint8_t *fragment;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
