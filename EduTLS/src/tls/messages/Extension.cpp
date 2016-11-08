//===-- EduTLS/src/tls/messages/Extension.cpp             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Extension protocol.
///
//===----------------------------------------------------------------------===//

#include "Extension.h"
#include "../enums/ExtensionType.h"
#include "../interfaces/encodable.h"

#include <cstdint>
#include <cstdlib>

Extension_t::Extension_t() {
  this->extension_data = NULL;
  this->extension_length = 0;
}
Extension_t::~Extension_t() {
  if (this->extension_data != NULL) {
    free(this->extension_data);
  }
}

int Extension_t::encode(uint8_t *result) {
  uint16_t type = static_cast<uint16_t>(this->extension_type);
  result[0] = (type >> 8) & 0xFF;
  result[1] = type & 0xFF;

  result[2] = (this->extension_length >> 8) & 0xFF;
  result[3] = this->extension_length & 0xFF;
  size_t i = 0;
  for (i = 0; i < this->extension_length; i++) {
    result[4 + i] = this->extension_data[i];
  }

  return 0;
}

size_t Extension_t::encode_length() { return 4 + this->extension_length; }

int Extension_t::decode(uint8_t *encoded, size_t length) {
  uint16_t type = (encoded[0] << 8) | encoded[1];
  this->extension_type = static_cast<ExtensionType_e>(type);

  this->extension_length = (encoded[2] << 8) | encoded[3];

  this->extension_data = (uint8_t *)malloc(sizeof(uint8_t) * this->extension_length);

  size_t i = 0;
  for (i = 0; i < this->extension_length && i + 4 < length; i++) {
    this->extension_data[i] = encoded[4 + i];
  }

  return 0;
}
