//===-- EduTLS/src/tls/messages/HelloRequest.h        -------*- C++ -*-===//
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

// Currently unused; bad practice to send a HelloRequest to the client before it
// sends an initial ClientHello.

class HelloRequest final : public HandshakeContents_t {
public:
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
