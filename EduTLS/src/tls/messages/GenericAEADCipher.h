//===-- EduTLS/src/tls/messages/GenericAEADCipher.h       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Generic AEAD Cipher protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./TLSCiphertext.h"

class GenericAEADCipher final : public encodable_i {
public:
  size_t nonce_length;
  uint8_t *nonce;
  size_t content_length;
  uint8_t *content;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
