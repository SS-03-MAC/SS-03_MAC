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
#include "../states/TLSSession.h"
#include "./TLSCompressed.h"

class CipherFragment_t : public encodable_i {
public:
  TLSCompressed *contents;

  virtual int encode(uint8_t *result) = 0;
  virtual size_t encode_length() = 0;
  virtual int decode(uint8_t *encoded, size_t length) = 0;

  virtual ~CipherFragment_t() {
    if (this->contents != NULL) {
      delete this->contents;
    }
  };
};

class TLSCiphertext final : public encodable_i {
public:
  ContentType_e type;
  ProtocolVersion_t version;
  uint16_t length;
  CipherFragment_t *fragment;

  TLSSession *state;

  TLSCiphertext(TLSSession *state);
  TLSCiphertext(TLSSession *state, CipherFragment_t *fragment);
  ~TLSCiphertext();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
