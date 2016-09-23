//===-- EduTLS/src/crypto/hash/md.h                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the abstract declaration of the Merkle–Damgård
/// construction for use in MD5, SHA1, and SHA2.
///
//===----------------------------------------------------------------------===//

#include "hash.h"

#include <cstddef>
#include <cstdint>

#pragma once

class md : public hash {
protected:
  bool le_padding;

  uint64_t t_len;

  uint8_t *block;
  size_t b_len;
  size_t b_max;

  virtual void core() = 0;
  virtual void digest(uint8_t *output) = 0;

public:
  void update(uint8_t *input, size_t count);
  void finalize(uint8_t *output);

  virtual void init() = 0;

  ~md() { delete[] this->block; };
};
