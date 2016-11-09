//===-- EduTLS/src/crypto/symmetric/des3.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the 3DES class which is a specific
/// implementation of the symmetric cipher class. This uses EDE mode.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "des.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>

class des3 final : public symmetric {
private:
  des *a;
  des *b;
  des *c;

public:
  uint64_t encrypt(uint64_t input);
  uint64_t decrypt(uint64_t input);

  int encrypt(uint8_t *output, uint8_t *input, size_t count);
  int decrypt(uint8_t *output, uint8_t *input, size_t count);

  des3(uint8_t *input, size_t count);
  des3(uint64_t key_1, uint64_t key_2, uint64_t key_3);
};
