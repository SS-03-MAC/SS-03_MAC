//===-- EduTLS/src/crypto/hash/hmac.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the HMAC class.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>

#include "./hash.h"

class hmac final : public hash {
private:
  hash *h;

  uint8_t *ipad;
  uint8_t *opad;
  uint8_t *key;

public:
  hmac(hash *h, uint8_t *key, size_t key_length);
  ~hmac();

  size_t block_size;
  size_t output_size;

  void update(uint8_t *input, size_t count);
  void finalize(uint8_t *output);
  void init();
};
