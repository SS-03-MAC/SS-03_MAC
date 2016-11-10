//===-- EduTLS/src/tls/messages/ServerKeyExchange.cpp     -------*- C++ -*-===//
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

#include "ServerKeyExchange.h"
#include <cstdint>

ServerKeyExchange::ServerKeyExchange() {}
ServerKeyExchange::~ServerKeyExchange() {}

int ServerKeyExchange::encode(uint8_t *) { return 0; }
size_t ServerKeyExchange::encode_length() { return 0; }
int ServerKeyExchange::decode(uint8_t *, size_t) { return 0; }
