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
#include <cstdint>

class ServerHelloDone final : public HandshakeContents_t {
public:
  ServerHelloDone();
  ~ServerHelloDone();

  int encode(uint8_t *);
  size_t encode_length();
  int decode(uint8_t *, size_t);
};
