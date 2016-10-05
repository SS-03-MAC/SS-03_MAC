//===-- EduTLS/src/crypto/block/ctr.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of CTR block mode with
///
//===----------------------------------------------------------------------===//

#include "../symmetric/symmetric.h"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

#pragma once

class ctr final : public symmetric {
private:
  symmetric *cipher;
  uint8_t *nonce;

public:
  inline int encrypt(uint8_t *output, uint8_t *input, size_t count) {
    uint8_t keystream[this->cipher->block_size / 8];
    uint64_t counter = 0;
    uint8_t key[this->cipher->block_size / 8];
    size_t i = 0;

    for (i = 0; i < this->cipher->block_size / 16; i++) {
      key[i] = this->nonce[i];
    }

    for (unsigned long i = 0; i < count; i += this->cipher->block_size / 8) {
      for (i = this->cipher->block_size / 16; i < this->cipher->block_size / 8; i++) {
        key[i] = count >> (((this->cipher->block_size / 16) * 4) - ((i - this->cipher->block_size / 16 + 1) * 8));
      }

      this->cipher->encrypt(keystream, key, this->cipher->block_size / 8);

      if ((this->cipher->block_size / 8) + i < count) {
        edutls_xor(output, input, keystream, this->cipher->block_size / 8);
      } else {
        edutls_xor(output, input, keystream, count - i);
      }

      output += this->cipher->block_size / 8;
      input += this->cipher->block_size / 8;
      counter += 1;
    }

    return 0;
  };

  inline int decrypt(uint8_t *output, uint8_t *input, size_t count) { return this->encrypt(output, input, count); };

  inline ctr(symmetric *cipher, uint8_t *nonce) {
    this->cipher = cipher;
    this->nonce = nonce;
  };
};
