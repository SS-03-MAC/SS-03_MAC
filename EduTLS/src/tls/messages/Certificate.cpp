//===-- EduTLS/src/tls/messages/Certificate.cpp             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Certificate protocol.
///
//===----------------------------------------------------------------------===//

#include "Certificate.h"
#include "../interfaces/encodable.h"
#include "Handshake.h"

#include <cstdio>

#include <cstdint>
#include <cstdlib>

Certificate_t::Certificate_t() {
  this->certificate_data = NULL;
  this->certificate_length = 0;
}
Certificate_t::~Certificate_t() {
  if (this->certificate_data != NULL) {
    free(this->certificate_data);
  }
}

int Certificate_t::encode(uint8_t *result) {
  result[0] = (this->certificate_length >> 16) & 0xFF;
  result[1] = (this->certificate_length >> 8) & 0xFF;
  result[2] = this->certificate_length & 0xFF;
  size_t i = 0;
  for (i = 0; i < this->certificate_length; i++) {
    result[3 + i] = this->certificate_data[i];
  }

  return 0;
}

size_t Certificate_t::encode_length() { return 3 + this->certificate_length; }

int Certificate_t::decode(uint8_t *encoded, size_t length) {
  this->certificate_length = (encoded[0] << 16) | (encoded[1] << 8) | encoded[2];

  this->certificate_data = (uint8_t *)malloc(sizeof(uint8_t) * this->certificate_length);

  size_t i = 0;
  for (i = 0; i < this->certificate_length && i + 3 < length; i++) {
    this->certificate_data[i] = encoded[3 + i];
  }

  return 0;
}

Certificate::Certificate() {
  this->certificates = NULL;
  this->certificates_length = 0;
}
Certificate::~Certificate() {
  if (this->certificates != NULL) {
    delete[] this->certificates;
  }
}

int Certificate::encode(uint8_t *result) {
  uint32_t length = 0;
  size_t i = 0;
  for (i = 0; i < this->certificates_length; i++) {
    length += this->certificates[i].encode_length();
  }

  result[0] = (length >> 16) & 0xFF;
  result[1] = (length >> 8) & 0xFF;
  result[2] = length & 0xFF;
  size_t r_p = 3;
  for (i = 0; i < this->certificates_length; i++) {
    this->certificates[i].encode(&(result[r_p]));
    r_p += this->certificates[i].encode_length();
  }

  return 0;
}

size_t Certificate::encode_length() {
  uint32_t length = 0;
  size_t i = 0;
  for (i = 0; i < this->certificates_length; i++) {
    length += this->certificates[i].encode_length();
  }
  return 3 + length;
}

int Certificate::decode(uint8_t *encoded, size_t length) {
  if (length < 3) {
    return 1;
  }

  this->certificates_length = (encoded[0] << 16) | (encoded[1] << 8) | encoded[2];

  this->certificates = new Certificate_t[this->certificates_length];

  /** TODO **/

  return 0;
}
