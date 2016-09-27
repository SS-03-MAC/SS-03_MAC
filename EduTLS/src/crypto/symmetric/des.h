//===-- EduTLS/src/crypto/symmetric/des.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the DES class which is a specific
/// implementation of the symmetric cipher class.
///
//===----------------------------------------------------------------------===//

#include "symmetric.h"

#include <cstddef>
#include <cstdint>

#pragma once

class des final : public symmetric {
private:
  uint64_t skey[16];

  void choice_1_permute(uint32_t *C, uint32_t *D, uint64_t key);
  void choice_2_permute(uint64_t *output, uint32_t C, uint32_t D);
  void initial_permute(uint32_t *left, uint32_t *right, uint64_t input);
  void inverse_permute(uint64_t *output, uint32_t left, uint32_t right);
  uint32_t permute_p(uint32_t input);
  uint64_t expand(uint32_t input);
  uint32_t f(uint32_t input, uint64_t key);

public:
  uint64_t encrypt(uint64_t input);
  uint64_t decrypt(uint64_t input);

  int encrypt(uint8_t *output, uint8_t *input, size_t count);
  int decrypt(uint8_t *output, uint8_t *input, size_t count);

  des(uint8_t *input, size_t count);
  des(uint64_t key);
};
