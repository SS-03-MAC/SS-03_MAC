//===-- EduTLS/src/crypto/symmetric/symmetric.h           -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the abstract declaration of the symmetric class.
///
//===----------------------------------------------------------------------===//

#include <cstdint>

#pragma once

class symmetric {
protected:
  uint8_t key_size;
  uint8_t block_size;

public:
  virtual symmetric *init(uint8_t *key, uint8_t key_size);
  virtual int encrypt(uint8_t *output, uint8_t input);
  virtual int decrypt(uint8_t *output, uint8_t input);
};
