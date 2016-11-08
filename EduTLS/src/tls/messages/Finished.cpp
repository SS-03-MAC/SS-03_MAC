//===-- EduTLS/src/tls/messages/Finished.cpp              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Finished protocol.
///
//===----------------------------------------------------------------------===//

#include "Finished.h"
#include "../interfaces/encodable.h"

#include <cstdint>
#include <cstdlib>

Finished::Finished() {
  this->verify_data = NULL;
  this->verify_data_length = 0;
}
Finished::~Finished() {
  if (this->verify_data != NULL) {
    free(this->verify_data);
  }
}

int Finished::encode(uint8_t *result) {
  size_t i = 0;
  for (i = 0; i < this->verify_data_length; i++) {
    result[i] = this->verify_data[i];
  }
  return 0;
}
size_t Finished::encode_length() { return this->verify_data_length; }

int Finished::decode(uint8_t *encoded, size_t length) {
  size_t i = 0;
  this->verify_data_length = length;
  this->verify_data = (uint8_t *)malloc(sizeof(uint8_t) * this->verify_data_length);
  for (i = 0; i < this->verify_data_length && i < length; i++) {
    this->verify_data[i] = encoded[i];
  }
  return 0;
}
