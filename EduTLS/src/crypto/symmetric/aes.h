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

#include "symmetric.h"

#include <cstddef>
#include <cstdint>

#pragma once

class aes final : public symmetric {
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

  void map(uint8_t *output, uint8_t *input);

public:
  static aes *aes_128(uint8_t key[16]);
  static aes *aes_192(uint8_t key[24]);
  static aes *aes_256(uint8_t key[32]);

  int encrypt(uint8_t *output, uint8_t *input, size_t count);
  int decrypt(uint8_t *output, uint8_t *input, size_t count);

  aes(uint8_t *key, size_t size);
  ~aes();

  uint32_t *__testing_copy_key();
};
