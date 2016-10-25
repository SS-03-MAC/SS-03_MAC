//===-- EduTLS/src/tls/containers/TLSCiphertext.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the TLS Ciphertext protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ContentType.h"
#include "../interfaces/encodable.h"
#include "../messages/ProtocolVersion.h"

class CipherFragment_t : public encodable_i {
public:
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};

class TLSCiphertext final : public encodable_i {
public:
  ContentType_e type;
  ProtocolVersion_t version;
  uint16_t length;
  CipherFragment_t *fragment;

  TLSCiphertext();
  TLSCiphertext(CipherFragment_t *fragment);
  ~TLSCiphertext();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
