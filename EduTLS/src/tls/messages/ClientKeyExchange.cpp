//===-- EduTLS/src/tls/messages/ClientKeyExchange.cpp     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Client Key Exchange protocol.
///
//===----------------------------------------------------------------------===//

#include "ClientKeyExchange.h"
#include <cstdint>

ClientKeyExchange::ClientKeyExchange() {}
ClientKeyExchange::~ClientKeyExchange() {}

int ClientKeyExchange::encode(uint8_t *) { return 0; }
size_t ClientKeyExchange::encode_length() { return 0; }
int ClientKeyExchange::decode(uint8_t *, size_t) { return 0; }
