//===-- EduTLS/src/crypto/block/ecb.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of ECB block mode with
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../symmetric/symmetric.h"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

class ecb final : public symmetric {
private:
  symmetric *cipher;

public:
  inline int encrypt(uint8_t *output, uint8_t *input, size_t count) {
    if (count * 8 % this->cipher->block_size != 0) {
      throw new std::invalid_argument("Invalid count for ECB mode.");
    }

    for (unsigned long i = 0; i < count / (this->cipher->block_size / 8); i++) {
      this->cipher->encrypt(output, input, this->cipher->block_size / 8);
      output += this->cipher->block_size / 8;
      input += this->cipher->block_size / 8;
    }

    return 0;
  };
  inline int decrypt(uint8_t *output, uint8_t *input, size_t count) {
    if (count * 8 % this->cipher->block_size != 0) {
      throw new std::invalid_argument("Invalid count for ECB mode.");
    }

    for (unsigned long i = 0; i < count / (this->cipher->block_size / 8); i++) {
      this->cipher->decrypt(output, input, this->cipher->block_size / 8);
      output += this->cipher->block_size / 8;
      input += this->cipher->block_size / 8;
    }

    return 0;
  };

  inline ecb(symmetric *cipher) { this->cipher = cipher; };
};
