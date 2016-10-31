//===-- EduTLS/src/tls/messages/ClientKeyExchange.h       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Client Key Exchange protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "Handshake.h"

class ClientKeyExchange : public HandshakeContents_t {
public:
  ClientKeyExchange();
  ~ClientKeyExchange();

  int encode(uint8_t *);
  size_t encode_length();
  int decode(uint8_t *, size_t);
};
