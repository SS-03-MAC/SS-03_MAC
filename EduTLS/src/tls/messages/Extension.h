//===-- EduTLS/src/tls/messages/Extension.h               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Extension protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"

class Extension_t final : public encodable_i {
public:
  ExtensionType_e extension_type;
  size_t extension_length;
  uint8_t *extension_data;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
