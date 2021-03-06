//===-- EduTLS/src/tls/messages/ClientHello.h             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Client Hello protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "Handshake.h"

#include "../enums/CompressionMethod.h"
#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"
#include "./Extension.h"
#include "./ProtocolVersion.h"
#include "./Random.h"

#include <cstdint>
#include <cstdlib>

class ClientHello final : public HandshakeContents_t {
public:
  ProtocolVersion_t client_version;
  Random_t random;

  uint8_t session_id_length;
  uint8_t *session_id;

  uint16_t cipher_suites_lengths;
  uint8_t *cipher_suites;

  uint8_t compression_methods_length;
  CompressionMethod_e *compression_methods;

  size_t extensions_length = 0;
  Extension_t *extensions;

  ClientHello();
  ~ClientHello();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
