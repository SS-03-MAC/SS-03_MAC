//===-- EduTLS/src/tls/messages/Alert.cpp             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Alert protocol.
///
//===----------------------------------------------------------------------===//

#include "Alert.h"
#include "../interfaces/encodable.h"
#include "Handshake.h"

#include <cstdio>

#include <cstdint>
#include <cstdlib>

int Alert::encode(uint8_t *result) {
  result[0] = static_cast<uint8_t>(this->level);
  result[1] = static_cast<uint8_t>(this->description);

  return 0;
}

size_t Alert::encode_length() { return 2; }

int Alert::decode(uint8_t *encoded, size_t length) {
  if (length != 2) {
    return 0;
  }

  this->level = static_cast<AlertLevel_e>(encoded[0]);
  this->description = static_cast<AlertDescription_e>(encoded[1]);

  return 0;
}
