//===-- EduTLS/src/crypto/hash/sha1.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of SHA1, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "sha1.h"
#include "../utils.h"
#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

uint32_t sha1::f(uint8_t t, uint32_t B, uint32_t C, uint32_t D) {
  if (t <= 19) {
    return (B & C) | ((~B) & D);
  } else if (20 <= t && t <= 39) {
    return (B ^ C) ^ D;
  } else if (40 <= t && t <= 59) {
    return (B & C) | (B & D) | (C & D);
  } else {
    return (B ^ C) ^ D;
  }
}

uint32_t sha1::k(uint8_t t) {
  if (t <= 19) {
    return 0x5A827999;
  } else if (20 <= t && t <= 39) {
    return 0x6ED9EBA1;
  } else if (40 <= t && t <= 59) {
    return 0x8F1BBCDC;
  } else {
    return 0xCA62C1D6;
  }
}

void sha1::core() {
  size_t t = 0;
  uint32_t w[80];
  uint32_t h[5];
  uint32_t temp;

  // Message has to be processed as a big endian integer
  for (t = 0; t < 16; t++) {
    w[t] = (((uint32_t)this->block[t * 4 + 0]) << 24) | (((uint32_t)this->block[t * 4 + 1]) << 16) |
           (((uint32_t)this->block[t * 4 + 2]) << 8) | (((uint32_t)this->block[t * 4 + 3]) << 0);
  }

  for (t = 16; t < 80; t++) {
    w[t] = edutls_rotl32(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
  }

  // Duplicate state into temporary variables
  h[0] = this->h[0];
  h[1] = this->h[1];
  h[2] = this->h[2];
  h[3] = this->h[3];
  h[4] = this->h[4];

  for (t = 0; t < 80; t++) {
    temp = edutls_rotl32(h[0], 5) + this->f(t, h[1], h[2], h[3]) + h[4] + w[t] + this->k(t);
    h[4] = h[3];
    h[3] = h[2];
    h[2] = edutls_rotl32(h[1], 30);
    h[1] = h[0];
    h[0] = temp;
  }

  // Add temporary variables back into state.
  this->h[0] += h[0];
  this->h[1] += h[1];
  this->h[2] += h[2];
  this->h[3] += h[3];
  this->h[4] += h[4];
}

void sha1::digest(uint8_t *output) {
  for (this->b_len = 0; this->b_len < 5; this->b_len++) {
    output[(this->b_len * 4) + 0] = (uint8_t)(this->h[this->b_len] >> 24);
    output[(this->b_len * 4) + 1] = (uint8_t)(this->h[this->b_len] >> 16);
    output[(this->b_len * 4) + 2] = (uint8_t)(this->h[this->b_len] >> 8);
    output[(this->b_len * 4) + 3] = (uint8_t)(this->h[this->b_len] >> 0);
  }
}

void sha1::init() {
  this->output_size = 20;
  this->le_padding = false;
  this->t_len = 0;
  this->b_len = 0;
  this->block_size = 64;

  this->block = new uint8_t[this->block_size];

  for (this->b_len = 0; this->b_len < this->block_size; this->b_len++) {
    this->block[this->b_len] = 0;
  }

  this->h[0] = 0x67452301;
  this->h[1] = 0xEFCDAB89;
  this->h[2] = 0x98BADCFE;
  this->h[3] = 0x10325476;
  this->h[4] = 0xC3D2E1F0;

  this->b_len = 0;
}
