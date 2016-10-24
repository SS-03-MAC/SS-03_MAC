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

#include "../enums/CompressionMethod.h"
#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"
#include "./ProtocolVersion.h"

class HandshakeType : public encodable_i {
public:
  HandshakeType_t type;
  uint24_t length;
  HandshakeContents_t body;
};

class HandshakeContents_t : public encodable_i {};
