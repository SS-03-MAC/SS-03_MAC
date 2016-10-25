//===-- EduTLS/src/tls/messages/TLSPlaintext.cpp          -------*- C++ -*-===//
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

TLSPlaintext::TLSPlaintext(ContentType_e type, ProtocolVersion_t version, uint16_t length, uint8_t *fragment) {
  this->type = type;
  this->version = version;
  this->length = length;
  this->fragment = (uint8_t *)malloc(sizeof(uint8_t) * length);

  size_t i = 0;
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
  result[0] = static_cast<uint8_t>(this->type);
  result[1] = this->version.major;
  result[2] = this->version.minor;
  result[3] = (this->length >> 8) & 0xFF;
  result[4] = this->length & 0xFF;
  for (i = 0; i < this->length; i++) {
    result[5 + i] = this->fragment[i];
  }

  return 0;
}

size_t TLSPlaintext::encode_length() { return 5 + this->length; }
int TLSPlaintext::decode(uint8_t *encoded) {
  size_t i = 0;

  if (encoded[0] < 20 || encoded[0] > 23) {
    return -1;
  }

  if (encoded[1] != 3 || encoded[2] > 4) {
    return -2;
  }

  this->type = static_cast<ContentType_e>(encoded[0]);
  this->version.major = encoded[1];
  this->version.minor = encoded[2];
  this->length = (encoded[3] << 8) | encoded[4];

  this->fragment = (uint8_t *)malloc(sizeof(uint8_t) * this->length);

  for (i = 0; i < this->length; i++) {
    this->fragment[i] = encoded[5 + i];
  }

  return 0;
}
