//===-- EduTLS/src/crypto/symmetric/rc4.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the RC4 class which is a specific
/// implementation of the symmetric cipher class.
///
//===----------------------------------------------------------------------===//

#include "symmetric.h"

#include <cstddef>
#include <cstdint>

#pragma once

class rc4 final : public symmetric {
private:
  uint8_t S[256];
  uint8_t x;
  uint8_t y;

public:
  void stream(uint8_t *data, size_t len);

  int encrypt(uint8_t *output, uint8_t *input, size_t count);
  int decrypt(uint8_t *output, uint8_t *input, size_t count);

  rc4(uint8_t *key, size_t keylen);
};
