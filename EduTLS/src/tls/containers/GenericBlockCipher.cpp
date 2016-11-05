//===-- EduTLS/src/tls/containers/GenericBlockCipher.cpp  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the Generic Block Cipher
/// protocol.
///
//===----------------------------------------------------------------------===//

#include "./GenericBlockCipher.h"
#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

GenericBlockCipher::GenericBlockCipher(TLSSession *state) {
  this->state = state;
  this->iv_length = this->state->current_read_params->fixed_iv_length;
  this->mac_length = this->state->current_read_params->mac_length;
}
GenericBlockCipher::~GenericBlockCipher() {}

int GenericBlockCipher::encode(uint8_t *) { return 0; }
size_t GenericBlockCipher::encode_length() { return 0; }
int GenericBlockCipher::decode(uint8_t *encoded, size_t length) {
  this->contents = NULL;

  printf("Encoded[0]: %02x\nLength: %zu\n", encoded[0], length);

  return 0;
}
