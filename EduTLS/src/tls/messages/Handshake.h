//===-- EduTLS/src/tls/messages/HandshakeType.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Handshake Type protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"

class HandshakeContents_t : public encodable_i {
public:
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};

class HandshakeType : public encodable_i {
public:
  HandshakeType_e type;
  uint32_t length : 24;
  HandshakeContents_t body;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
