//===-- EduTLS/src/tls/containers/TLSCiphertext.cpp       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the TLS Ciphertext protocol.
///
//===----------------------------------------------------------------------===//

#include "./TLSCiphertext.h"
#include "../abstractions/CipherFragmentFactory.h"
#include "../states/TLSSession.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

TLSCiphertext::TLSCiphertext(TLSSession *state) {
  this->fragment = NULL;
  this->state = state;
}
TLSCiphertext::TLSCiphertext(TLSSession *state, CipherFragment_t *fragment) {
  this->fragment = fragment;
  this->state = state;
  this->length = fragment->encode_length();
}
TLSCiphertext::~TLSCiphertext() {
  if (this->fragment != NULL) {
    delete this->fragment;
  }
}

int TLSCiphertext::encode(uint8_t *result) {
  result[0] = static_cast<uint8_t>(this->type);
  result[1] = this->version.major;
  result[2] = this->version.minor;
  result[3] = (this->length >> 8) & 0xFF;
  result[4] = this->length & 0xFF;

  return this->fragment->encode(&(result[5]));
}

size_t TLSCiphertext::encode_length() { return 5 + this->length; }

int TLSCiphertext::decode(uint8_t *encoded, size_t length) {
  if (encoded[0] < 20 || encoded[0] > 23) {
    return -1;
  }

  if (encoded[1] != 3 || encoded[2] > 4) {
    return -2;
  }

  this->type = static_cast<ContentType_e>(encoded[0]);
  this->version.major = encoded[1];
  this->version.minor = encoded[2];
  this->length = (((uint16_t)encoded[3]) << 8) | encoded[4];

  if (this->length != length - 5) {
    return -3;
  }

  printf("Current READ Cipher type: %d\n", static_cast<int>(this->state->current_read_params->cipher_type));

  this->fragment = CipherFragment_f::Construct(this->state->current_read_params->cipher_type, this->state);

  if (this->fragment == NULL) {
    return -4;
  }

  return this->fragment->decode(&(encoded[5]), this->length);
}
