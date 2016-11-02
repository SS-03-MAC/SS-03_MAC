//===-- EduTLS/src/crypto/hash/hash.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the abstract declaration of the hash class.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>

class hash {
public:
  size_t output_size;
  size_t block_size;

  ~hash(){};

  virtual void init() = 0;
  virtual void update(uint8_t *input, size_t count) = 0;
  virtual void finalize(uint8_t *output) = 0;

  inline void sum(uint8_t *output, uint8_t *input, size_t count) {
    this->init();
    this->update(input, count);
    this->finalize(output);
  };
};
