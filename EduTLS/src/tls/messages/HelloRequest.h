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

#include "Handshake.h"
#include "../interfaces/encodable.h"

final class HelloRequest : public HandshakeContents_t {
public:
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
