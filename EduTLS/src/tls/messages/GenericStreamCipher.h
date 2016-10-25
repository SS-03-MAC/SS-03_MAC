//===-- EduTLS/src/tls/messages/GenericStreamCipher.h     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Generic Stream Cipher protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./TLSCiphertext.h"

class GenericStreamCipher final : public encodable_i {
public:
  size_t content_length;
  uint8_t *content;
  size_t mac_length;
  uint8_t *mac;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
