//===-- EduTLS/src/tls/containers/GenericStreamCipher.h   -------*- C++ -*-===//
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

#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdlib>

class GenericStreamCipher final : public CipherFragment_t {
public:
  uint16_t contents_length;
  uint8_t *ciphertext;
  TLSCompressed *contents;
  uint8_t mac_length;
  uint8_t *mac;

  TLSSession *state;

  GenericStreamCipher(TLSSession *state);
  GenericStreamCipher(TLSSession *state, TLSCompressed *contents);
  ~GenericStreamCipher();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
