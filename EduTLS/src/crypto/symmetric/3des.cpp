//===-- EduTLS/src/crypto/symmetric/des33.cpp              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the 3des3 class core methods.
///
//===----------------------------------------------------------------------===//

#include "3des.h"
#include "../utils.h"
#include "des.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>

des3::des3(uint64_t key_1, uint64_t key_2, uint64_t key_3) {
  this->a = new des(key_1);
  this->b = new des(key_2);
  this->c = new des(key_3);
}

des3::des3(uint8_t *input, size_t count) {
  if (count != 24) {
    throw new std::invalid_argument("Invalid key size for DES.");
  }

  this->a = new des(&input[0], 8);
  this->b = new des(&input[8], 8);
  this->c = new des(&input[16], 8);

  this->block_size = 64;
}

uint64_t des3::encrypt(uint64_t input) {
  uint64_t result = input;
  result = this->a->encrypt(result);
  result = this->b->decrypt(result);
  result = this->c->encrypt(result);

  return result;
}

uint64_t des3::decrypt(uint64_t input) {
  uint64_t result = input;
  result = this->a->decrypt(result);
  result = this->b->encrypt(result);
  result = this->c->decrypt(result);

  return result;
}

int des3::encrypt(uint8_t *output, uint8_t *input, size_t count) {
  this->a->encrypt(output, input, count);
  this->b->encrypt(output, output, count);
  this->c->encrypt(output, output, count);

  return 0;
}

int des3::decrypt(uint8_t *output, uint8_t *input, size_t count) {
  this->a->encrypt(output, input, count);
  this->b->encrypt(output, output, count);
  this->c->encrypt(output, output, count);

  return 0;
}
