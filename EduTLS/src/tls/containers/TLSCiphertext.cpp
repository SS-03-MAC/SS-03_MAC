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
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

TLSCiphertext::TLSCiphertext() { this->fragment = NULL; }
TLSCiphertext::TLSCiphertext(CipherFragment_t *fragment) { this->fragment = fragment; }
TLSCiphertext::~TLSCiphertext() {}

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

  return this->fragment->decode(&(encoded[5]), length - 5);
}
