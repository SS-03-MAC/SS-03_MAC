//===-- EduTLS/src/tls/messages/ServerDHParams.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Hello Request protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "Handshake.h"

class ServerKeyExchange : public HandshakeContents_t {
public:
  ServerKeyExchange();
  ~ServerKeyExchange();

  int encode(uint8_t *);
  size_t encode_length();
  int decode(uint8_t *, size_t);
};
