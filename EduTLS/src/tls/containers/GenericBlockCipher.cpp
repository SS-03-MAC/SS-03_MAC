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
#include "../../crypto/crypto.h"
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
  uint8_t iv[this->state->current_read_params->record_iv_length];
  printf("IV Length: %d\n", this->state->current_read_params->record_iv_length);
  size_t i = 0;
  for (i = 0; i < this->state->current_read_params->record_iv_length; i++) {
    iv[i] = encoded[i];
  }
  uint8_t data[length - this->state->current_read_params->record_iv_length];
  printf("Data Length: %zu\n", length - this->state->current_read_params->record_iv_length);

  aes *cipher = new aes(this->state->current_read_params->cipher_key, this->state->current_read_params->enc_key_length);
  cbc *block_mode = new cbc(cipher, iv);
  block_mode->decrypt(data, &(encoded[this->state->current_read_params->record_iv_length]),
                      length - this->state->current_read_params->record_iv_length);

  printf("Data!? :D Nom nom\n");
  i = 0;
  for (i = 0; i < length - this->state->current_read_params->record_iv_length; i++) {
    printf("%02x", data[i]);
  }
  printf("\n");

  this->contents = NULL;

  printf("Encoded[0]: %02x\nLength: %zu\n", encoded[0], length);

  return 0;
}
