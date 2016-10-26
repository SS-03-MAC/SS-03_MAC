//===-- EduTLS/src/tls/messages/ServerHello.cpp           -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Server Hello protocol.
///
//===----------------------------------------------------------------------===//

#include "ServerHello.h"
#include "Handshake.h"

#include "../enums/CompressionMethod.h"
#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"
#include "./Extension.h"
#include "./ProtocolVersion.h"
#include "./Random.h"

ServerHello::ServerHello() {}
ServerHello::~ServerHello() {}

int ServerHello::encode(uint8_t *result) { return 0; }
size_t ServerHello::encode_length() { return 0; }
int ServerHello::decode(uint8_t *encoded, size_t length) { return 0; }
