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
    if (this->b_len == this->b_max) {
      this->b_len = 0;

      this->core();
    }

    this->block[this->b_len] = (uint8_t)((unsigned char)input[i]);
    this->b_len += 1;
  }
};

void md::finalize(uint8_t *output) {
  if (this->b_len > b_max - 8 - 1) {
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

  for (; this->b_len < b_max; this->b_len++) {
    this->block[this->b_len] = 0x00;
  }

  this->t_len *= 8;

  if (this->le_padding) {
    this->block[b_max - 8] = (uint8_t)(this->t_len >> 0);
    this->block[b_max - 7] = (uint8_t)(this->t_len >> 8);
    this->block[b_max - 6] = (uint8_t)(this->t_len >> 16);
    this->block[b_max - 5] = (uint8_t)(this->t_len >> 24);
    this->block[b_max - 4] = (uint8_t)(this->t_len >> 32);
    this->block[b_max - 3] = (uint8_t)(this->t_len >> 40);
    this->block[b_max - 2] = (uint8_t)(this->t_len >> 48);
    this->block[b_max - 1] = (uint8_t)(this->t_len >> 56);
  } else {
    this->block[b_max - 8] = (uint8_t)(this->t_len >> 56);
    this->block[b_max - 7] = (uint8_t)(this->t_len >> 48);
    this->block[b_max - 6] = (uint8_t)(this->t_len >> 40);
    this->block[b_max - 5] = (uint8_t)(this->t_len >> 32);
    this->block[b_max - 4] = (uint8_t)(this->t_len >> 24);
    this->block[b_max - 3] = (uint8_t)(this->t_len >> 16);
    this->block[b_max - 2] = (uint8_t)(this->t_len >> 8);
    this->block[b_max - 1] = (uint8_t)(this->t_len >> 0);
  }

  this->core();

  this->digest(output);
  this->b_len = 0;
};