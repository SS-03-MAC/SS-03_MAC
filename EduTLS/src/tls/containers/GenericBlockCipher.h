//===-- EduTLS/src/tls/containers/GenericBlockCipher.h    -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Generic Block Cipher protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"

class GenericBlockCipher final : public CipherFragment_t {
public:
  size_t iv_length;
  uint8_t *iv;
  size_t content_length;
  uint8_t *content;
  size_t mac_length;
  uint8_t *mac;

  uint8_t padding_length;
  uint8_t *padding;

  TLSSession *state;

  GenericBlockCipher(TLSSession *state);
  GenericBlockCipher(TLSSession *state, TLSCompressed *contents);
  ~GenericBlockCipher();

  int encode(uint8_t *);
  size_t encode_length();
  int decode(uint8_t *, size_t);
};
