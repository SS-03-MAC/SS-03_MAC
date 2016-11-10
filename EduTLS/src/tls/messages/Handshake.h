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

#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"

class HandshakeContents_t : public encodable_i {
public:
  virtual int encode(uint8_t *result) = 0;
  virtual size_t encode_length() = 0;
  virtual int decode(uint8_t *encoded, size_t length) = 0;

  virtual ~HandshakeContents_t(){};
};

class HandshakeType final : public encodable_i {
public:
  HandshakeType_e type;
  uint32_t length : 24;
  HandshakeContents_t *body;

  HandshakeType();
  HandshakeType(HandshakeContents_t *body);
  ~HandshakeType();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
