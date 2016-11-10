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

#pragma once

#include <cstddef>
#include <cstdint>

class symmetric {
public:
  uint8_t key_size;
  uint8_t block_size;

  virtual int encrypt(uint8_t *output, uint8_t *input, size_t count) = 0;
  virtual int decrypt(uint8_t *output, uint8_t *input, size_t count) = 0;
};
