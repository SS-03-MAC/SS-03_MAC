//===-- EduTLS/src/crypto/symmetric/rc4.cpp               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the RC4 class core methods.
///
//===----------------------------------------------------------------------===//

#include "rc4.h"
#include "../utils.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>

rc4::rc4(uint8_t *key, size_t keylen) {

  size_t i = 0;
  uint8_t j = 0;
  uint8_t tmp;

  for (i = 0; i < 256; i++) {
    this->S[i] = (uint8_t)i;
  }

  this->x = 0;
  this->y = 0;

  for (i = 0; i < 256; i++) {
    j = j + this->S[i] + key[i % keylen];

    tmp = this->S[i];
    this->S[i] = this->S[j];
    this->S[j] = tmp;
  }
}

void rc4::stream(uint8_t *data, size_t len) {

  size_t i = 0;
  uint8_t x = 0;
  uint8_t tmp;

  for (i = 0; i < len; i++) {
    this->x = this->x + 1;
    this->y = this->S[this->x] + this->y;

    tmp = this->S[this->x];
    this->S[this->x] = this->S[this->y];
    this->S[this->y] = tmp;

    x = this->S[this->x] + this->S[this->y];

    data[i] = this->S[x];
  }
}

int rc4::encrypt(uint8_t *output, uint8_t *input, size_t count) {
  uint8_t keystream[count];
  this->stream(keystream, count);
  edutls_xor(output, input, keystream, count);
  return 0;
}

int rc4::decrypt(uint8_t *output, uint8_t *input, size_t count) {
  uint8_t keystream[count];
  this->stream(keystream, count);
  edutls_xor(output, input, keystream, count);
  return 0;
}
