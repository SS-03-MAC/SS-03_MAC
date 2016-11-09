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
#include "../states/TLSConfiguration.h"
#include "../states/TLSSession.h"
#include "Handshake.h"
#include "ProtocolVersion.h"

class ClientKeyExchange : public HandshakeContents_t {
public:
  ProtocolVersion_t client_version;
  uint8_t random[46];

  uint16_t length;
  uint8_t *encrypted;

  ClientKeyExchange();
  ~ClientKeyExchange();

  int encrypt(TLSSession *state, TLSConfiguration *config);
  int decrypt(TLSSession *state, TLSConfiguration *config);

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
