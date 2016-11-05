//===-- EduTLS/src/tls/messages/ChangeCipherSpec.cpp     -------*- C++ -*-===//
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

#include "ChangeCipherSpec.h"
#include "../enums/ChangeCipherSpec.h"
#include <cstdint>

ChangeCipherSpec::ChangeCipherSpec() {}
ChangeCipherSpec::~ChangeCipherSpec() {}

int ChangeCipherSpec::encode(uint8_t *result) {
  result[0] = static_cast<uint8_t>(this->value);
  return 0;
}

size_t ChangeCipherSpec::encode_length() { return 1; }
int ChangeCipherSpec::decode(uint8_t *encoded, size_t length) {
  if (length != 1) {
    return 1;
  }

  this->value = static_cast<ChangeCipherSpec_e>(encoded[0]);
  return 0;
}
