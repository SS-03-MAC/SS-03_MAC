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

class hmac {
private:
  hash *h;

  uint8_t *ipad;
  uint8_t *opad;
  uint8_t *key;

  size_t block_length;
  size_t output_length;

public:
  hmac(hash *h, uint8_t *key, size_t key_length);
  ~hmac();

  void sum(uint8_t *result, uint8_t *text, size_t text_length);
};
