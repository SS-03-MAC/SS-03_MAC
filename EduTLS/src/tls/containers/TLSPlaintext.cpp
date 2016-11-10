//===-- EduTLS/src/tls/containers/TLSPlaintext.cpp        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the TLS Plaintext protocol.
///
//===----------------------------------------------------------------------===//

#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

TLSPlaintext::TLSPlaintext() { this->fragment = NULL; }

TLSPlaintext::TLSPlaintext(uint16_t length, uint8_t *fragment) {
  size_t i = 0;

  this->length = length;
  this->fragment = (uint8_t *)malloc(sizeof(uint8_t) * length);
  for (i = 0; i < length; i++) {
    this->fragment[i] = fragment[i];
  }
}

TLSPlaintext::~TLSPlaintext() {
  if (this->fragment != NULL) {
    free(this->fragment);
  }
}

int TLSPlaintext::encode(uint8_t *result) {
  size_t i = 0;
  for (i = 0; i < this->length; i++) {
    result[i] = this->fragment[i];
  }

  return 0;
}

size_t TLSPlaintext::encode_length() { return this->length; }

int TLSPlaintext::decode(uint8_t *encoded, size_t length) {
  this->length = length;

  this->fragment = (uint8_t *)malloc(sizeof(uint8_t) * length);

  size_t i = 0;
  for (i = 0; i < this->length; i++) {
    this->fragment[i] = encoded[i];
  }

  return 0;
}
