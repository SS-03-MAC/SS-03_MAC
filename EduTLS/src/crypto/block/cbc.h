//===-- EduTLS/src/crypto/block/cbc.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of CBC block mode with
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../symmetric/symmetric.h"
#include "../utils.h"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

class cbc final : public symmetric {
private:
  symmetric *cipher;
  uint8_t *iv;

public:
  inline int encrypt(uint8_t *output, uint8_t *input, size_t count) {
    if (count * 8 % this->cipher->block_size != 0) {
      throw new std::invalid_argument("Invalid count for CBC mode.");
    }

    uint8_t *prev = iv;

    for (unsigned long i = 0; i < count / (this->cipher->block_size / 8); i++) {
      edutls_xor(output, input, prev, this->cipher->block_size / 8);
      this->cipher->encrypt(output, output, this->cipher->block_size / 8);
      output += this->cipher->block_size / 8;
      input += this->cipher->block_size / 8;
    }

    return 0;
  };
  inline int decrypt(uint8_t *output, uint8_t *input, size_t count) {
    if (count * 8 % this->cipher->block_size != 0) {
      throw new std::invalid_argument("Invalid count for CBC mode.");
    }

    uint8_t *prev = iv;

    for (unsigned long i = 0; i < count / (this->cipher->block_size / 8); i++) {
      this->cipher->decrypt(output, input, this->cipher->block_size / 8);
      edutls_xor(output, output, prev, this->cipher->block_size / 8);
      output += this->cipher->block_size / 8;
      input += this->cipher->block_size / 8;
    }

    return 0;
  };

  inline cbc(symmetric *cipher, uint8_t *iv) {
    this->cipher = cipher;
    this->iv = iv;
  };
};
