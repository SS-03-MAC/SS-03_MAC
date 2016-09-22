//===-- EduTLS/src/crypto/symmetric/aes.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the AES class which is a specific
/// implementation of the symmetric cipher class.
///
//===----------------------------------------------------------------------===//

#include "../constants/aes.h"
#include "../utils.h"
#include "symmetric.h"

#include <cstddef>
#include <cstdint>

#pragma once

class aes : public symmetric {
private:
  uint32_t *key;
  uint8_t block[16];

  size_t rounds;

  uint32_t sub_word(uint32_t input);
  void add_round_key(uint8_t round);
  void sub_bytes();
  void shift_rows();
  void mix_columns();
  void inverse_sub_bytes();
  void inverse_shift_rows();
  void inverse_mix_columns();

public:
  aes *aes_128(uint8_t key[16]);
  aes *aes_192(uint8_t key[24]);
  aes *aes_256(uint8_t key[32]);

  symmetric *init(uint8_t *key, uint8_t key_size);
  int encrypt(uint8_t *output, uint8_t input);
  int decrypt(uint8_t *output, uint8_t input);

  aes(uint8_t *key, size_t size);
  ~aes();
};
