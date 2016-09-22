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
private:
  uint8_t *key;
  uint8_t blocksize;

public:
  virtual int init(uint8_t key, uint8_t key_size);
  virtual int encrypt(uint8_t *output, uint8_t input);
  virtual int decrypt(uint8_t *output, uint8_t input);
};
