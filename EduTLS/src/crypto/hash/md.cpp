//===-- EduTLS/src/crypto/hash/md.cpp                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the Merkle–Damgård
/// construction for use in MD5, SHA1, and SHA2.
///
//===----------------------------------------------------------------------===//

#include "md.h"
#include "hash.h"

#include <cstddef>
#include <cstdint>

void md::update(uint8_t *input, size_t count) {
  size_t i = 0;

  this->t_len += count;
  for (i = 0; i < count; i++) {
    if (this->b_len == this->block_size) {
      this->b_len = 0;

      this->core();
    }

    this->block[this->b_len] = (uint8_t)((unsigned char)input[i]);
    this->b_len += 1;
  }
};

void md::finalize(uint8_t *output) {
  if (this->b_len > block_size - 8 - 1) {
    this->block[this->b_len] = 0x80;
    this->b_len += 1;

    for (; this->b_len < 64; this->b_len++) {
      this->block[this->b_len] = 0x00;
    }

    this->b_len = 0;

    this->core();
  } else {
    this->block[this->b_len] = 0x80;
    this->b_len += 1;
  }

  for (; this->b_len < block_size; this->b_len++) {
    this->block[this->b_len] = 0x00;
  }

  this->t_len *= 8;

  if (this->le_padding) {
    this->block[block_size - 8] = (uint8_t)(this->t_len >> 0);
    this->block[block_size - 7] = (uint8_t)(this->t_len >> 8);
    this->block[block_size - 6] = (uint8_t)(this->t_len >> 16);
    this->block[block_size - 5] = (uint8_t)(this->t_len >> 24);
    this->block[block_size - 4] = (uint8_t)(this->t_len >> 32);
    this->block[block_size - 3] = (uint8_t)(this->t_len >> 40);
    this->block[block_size - 2] = (uint8_t)(this->t_len >> 48);
    this->block[block_size - 1] = (uint8_t)(this->t_len >> 56);
  } else {
    this->block[block_size - 8] = (uint8_t)(this->t_len >> 56);
    this->block[block_size - 7] = (uint8_t)(this->t_len >> 48);
    this->block[block_size - 6] = (uint8_t)(this->t_len >> 40);
    this->block[block_size - 5] = (uint8_t)(this->t_len >> 32);
    this->block[block_size - 4] = (uint8_t)(this->t_len >> 24);
    this->block[block_size - 3] = (uint8_t)(this->t_len >> 16);
    this->block[block_size - 2] = (uint8_t)(this->t_len >> 8);
    this->block[block_size - 1] = (uint8_t)(this->t_len >> 0);
  }

  this->core();

  this->digest(output);
  this->b_len = 0;
};
