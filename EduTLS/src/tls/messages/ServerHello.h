//===-- EduTLS/src/tls/messages/ServerHello.h             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Server Hello protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "Handshake.h"

#include "../enums/CompressionMethod.h"
#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"
#include "./ProtocolVersion.h"

final class ServerHello : public HandshakeContents_t {
public:
  ProtocolVersion_t server_version;
  Random_t random;

  size_t session_id_length;
  uint8_t *session_id;

  uint8_t cipher_suite[2];

  CompressionMethod_t compression_method;

  size_t extensions_length = 0;
  Extension_t *extensions;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
