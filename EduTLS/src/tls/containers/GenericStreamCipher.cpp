//===-- EduTLS/src/tls/containers/GenericStreamCipher.cpp -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the Generic Stream Cipher
/// protocol.
///
//===----------------------------------------------------------------------===//

#include "./GenericStreamCipher.h"
#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

// Currently only implements the NULL cipher; extend later to RC4 and AES-CTR
// if desired.

GenericStreamCipher::GenericStreamCipher(TLSSession *state) {
  this->ciphertext = NULL;
  this->mac_length = 0;
  this->contents_length = 0;
  this->state = state;
  this->contents = NULL;
}
GenericStreamCipher::GenericStreamCipher(TLSSession *state, TLSCompressed *contents) {
  this->contents = contents;
  this->contents_length = this->contents->encode_length();
  this->ciphertext = (uint8_t *)malloc(sizeof(uint8_t) * this->contents->encode_length());
  this->contents->encode(this->ciphertext);
  this->mac_length = 0;
  this->state = state;
}
GenericStreamCipher::~GenericStreamCipher() {
  if (this->ciphertext != NULL) {
    free(this->ciphertext);
  }
}

int GenericStreamCipher::encode(uint8_t *result) {
  size_t i = 0;
  for (i = 0; i < this->contents_length; i++) {
    result[i] = this->ciphertext[i];
  }

  for (i = 0; i < this->mac_length; i++) {
    result[i + this->contents_length] = this->mac[i];
  }

  return 0;
}

size_t GenericStreamCipher::encode_length() { return this->contents_length + this->mac_length; }

int GenericStreamCipher::decode(uint8_t *encoded, size_t length) {
  size_t i = 0;
  this->contents_length = length - this->mac_length;

  if (this->ciphertext != NULL) {
    free(this->ciphertext);
  }

  this->ciphertext = (uint8_t *)malloc(sizeof(uint8_t) * this->contents_length);

  for (i = 0; i < this->contents_length; i++) {
    this->ciphertext[i] = encoded[i];
  }

  for (i = 0; i < this->mac_length; i++) {
    this->mac[i] = encoded[i + this->contents_length];
  }

  this->contents = new TLSCompressed(this->state);

  return this->contents->decode(this->ciphertext, this->contents_length);
}
