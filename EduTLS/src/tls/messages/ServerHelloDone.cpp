//===-- EduTLS/src/tls/messages/ServerHelloDone.cpp     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Server Key Exchange protocol.
///
//===----------------------------------------------------------------------===//

#include "ServerHelloDone.h"
#include <cstdint>

ServerHelloDone::ServerHelloDone() {}
ServerHelloDone::~ServerHelloDone() {}

int ServerHelloDone::encode(uint8_t *) { return 0; }
size_t ServerHelloDone::encode_length() { return 0; }
int ServerHelloDone::decode(uint8_t *, size_t) { return 0; }
