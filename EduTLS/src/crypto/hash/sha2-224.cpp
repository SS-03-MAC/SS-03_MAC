//===-- EduTLS/src/crypto/hash/sha2-224.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of SHA2-224, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "sha2-224.h"
#include "../utils.h"
#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

uint32_t sha2_224::ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ ((~x) & z); }

uint32_t sha2_224::mj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }

uint32_t sha2_224::bsig0(uint32_t x) { return edutls_rotr32(x, 2) ^ edutls_rotr32(x, 13) ^ edutls_rotr32(x, 22); }

uint32_t sha2_224::bsig1(uint32_t x) { return edutls_rotr32(x, 6) ^ edutls_rotr32(x, 11) ^ edutls_rotr32(x, 25); }

uint32_t sha2_224::ssig0(uint32_t x) { return edutls_rotr32(x, 7) ^ edutls_rotr32(x, 18) ^ (x >> 3); }

uint32_t sha2_224::ssig1(uint32_t x) { return edutls_rotr32(x, 17) ^ edutls_rotr32(x, 19) ^ (x >> 10); }

void sha2_224::core() {

  size_t t = 0;
  uint32_t w[64];
  uint32_t h[8];
  uint32_t tmp1;
  uint32_t tmp2;

  static const uint32_t K[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
      0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
      0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
      0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
      0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  for (t = 0; t < 16; t++) {
    w[t] = (((uint32_t)this->block[t * 4 + 0]) << 24) | (((uint32_t)this->block[t * 4 + 1]) << 16) |
           (((uint32_t)this->block[t * 4 + 2]) << 8) | (((uint32_t)this->block[t * 4 + 3]) << 0);
  }

  for (t = 16; t < 64; t++) {
    w[t] = this->ssig1(w[t - 2]) + w[t - 7] + this->ssig0(w[t - 15]) + w[t - 16];
  }

  h[0] = this->h[0];
  h[1] = this->h[1];
  h[2] = this->h[2];
  h[3] = this->h[3];
  h[4] = this->h[4];
  h[5] = this->h[5];
  h[6] = this->h[6];
  h[7] = this->h[7];

  for (t = 0; t < 64; t++) {
    tmp1 = h[7] + this->bsig1(h[4]) + this->ch(h[4], h[5], h[6]) + K[t] + w[t];
    tmp2 = this->bsig0(h[0]) + this->mj(h[0], h[1], h[2]);

    h[7] = h[6];
    h[6] = h[5];
    h[5] = h[4];
    h[4] = h[3] + tmp1;
    h[3] = h[2];
    h[2] = h[1];
    h[1] = h[0];
    h[0] = tmp1 + tmp2;
  }

  this->h[0] += h[0];
  this->h[1] += h[1];
  this->h[2] += h[2];
  this->h[3] += h[3];
  this->h[4] += h[4];
  this->h[5] += h[5];
  this->h[6] += h[6];
  this->h[7] += h[7];
}

void sha2_224::digest(uint8_t *output) {
  for (this->b_len = 0; this->b_len < 7; this->b_len++) {
    output[(this->b_len * 4) + 0] = (uint8_t)(this->h[this->b_len] >> 24);
    output[(this->b_len * 4) + 1] = (uint8_t)(this->h[this->b_len] >> 16);
    output[(this->b_len * 4) + 2] = (uint8_t)(this->h[this->b_len] >> 8);
    output[(this->b_len * 4) + 3] = (uint8_t)(this->h[this->b_len] >> 0);
  }
}

void sha2_224::init() {
  this->output_size = 28;
  this->le_padding = false;
  this->t_len = 0;
  this->b_len = 0;
  this->block_size = 64;

  this->block = new uint8_t[this->block_size];

  for (this->b_len = 0; this->b_len < this->block_size; this->b_len++) {
    this->block[this->b_len] = 0;
  }

  this->h[0] = 0xc1059ed8;
  this->h[1] = 0x367cd507;
  this->h[2] = 0x3070dd17;
  this->h[3] = 0xf70e5939;
  this->h[4] = 0xffc00b31;
  this->h[5] = 0x68581511;
  this->h[6] = 0x64f98fa7;
  this->h[7] = 0xbefa4fa4;

  this->b_len = 0;
}
