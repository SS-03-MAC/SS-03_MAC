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

class ServerHelloDone final : public HandshakeContents_t {
public:
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
