//===-- EduTLS/src/crypto/hash/md5.h                      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of MD5, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "md5.h"
#include "../utils.h"
#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

uint32_t md5::f(uint32_t X, uint32_t Y, uint32_t Z) { return ((Y ^ Z) & X) ^ Z; }

uint32_t md5::g(uint32_t X, uint32_t Y, uint32_t Z) { return ((X ^ Y) & Z) ^ Y; }

uint32_t md5::h(uint32_t X, uint32_t Y, uint32_t Z) { return (X ^ Y) ^ Z; }

uint32_t md5::i(uint32_t X, uint32_t Y, uint32_t Z) { return (Y ^ (X | (~Z))); }

void md5::core() {
  size_t i = 0;
  uint32_t x[16];
  uint32_t s[4];

  for (i = 0; i < 16; i++) {
    x[i] = (((uint32_t)this->block[i * 4 + 3]) << 24) | (((uint32_t)this->block[i * 4 + 2]) << 16) |
           (((uint32_t)this->block[i * 4 + 1]) << 8) | (((uint32_t)this->block[i * 4 + 0]) << 0);
  }

  s[0] = this->s[0];
  s[1] = this->s[1];
  s[2] = this->s[2];
  s[3] = this->s[3];

  // Round 1
  s[0] = s[1] + edutls_rotl32(s[0] + this->f(s[1], s[2], s[3]) + x[0] + 0xd76aa478, 7);
  s[3] = s[0] + edutls_rotl32(s[3] + this->f(s[0], s[1], s[2]) + x[1] + 0xe8c7b756, 12);
  s[2] = s[3] + edutls_rotl32(s[2] + this->f(s[3], s[0], s[1]) + x[2] + 0x242070db, 17);
  s[1] = s[2] + edutls_rotl32(s[1] + this->f(s[2], s[3], s[0]) + x[3] + 0xc1bdceee, 22);
  s[0] = s[1] + edutls_rotl32(s[0] + this->f(s[1], s[2], s[3]) + x[4] + 0xf57c0faf, 7);
  s[3] = s[0] + edutls_rotl32(s[3] + this->f(s[0], s[1], s[2]) + x[5] + 0x4787c62a, 12);
  s[2] = s[3] + edutls_rotl32(s[2] + this->f(s[3], s[0], s[1]) + x[6] + 0xa8304613, 17);
  s[1] = s[2] + edutls_rotl32(s[1] + this->f(s[2], s[3], s[0]) + x[7] + 0xfd469501, 22);
  s[0] = s[1] + edutls_rotl32(s[0] + this->f(s[1], s[2], s[3]) + x[8] + 0x698098d8, 7);
  s[3] = s[0] + edutls_rotl32(s[3] + this->f(s[0], s[1], s[2]) + x[9] + 0x8b44f7af, 12);
  s[2] = s[3] + edutls_rotl32(s[2] + this->f(s[3], s[0], s[1]) + x[10] + 0xffff5bb1, 17);
  s[1] = s[2] + edutls_rotl32(s[1] + this->f(s[2], s[3], s[0]) + x[11] + 0x895cd7be, 22);
  s[0] = s[1] + edutls_rotl32(s[0] + this->f(s[1], s[2], s[3]) + x[12] + 0x6b901122, 7);
  s[3] = s[0] + edutls_rotl32(s[3] + this->f(s[0], s[1], s[2]) + x[13] + 0xfd987193, 12);
  s[2] = s[3] + edutls_rotl32(s[2] + this->f(s[3], s[0], s[1]) + x[14] + 0xa679438e, 17);
  s[1] = s[2] + edutls_rotl32(s[1] + this->f(s[2], s[3], s[0]) + x[15] + 0x49b40821, 22);

  // Round 2
  s[0] = s[1] + edutls_rotl32(s[0] + this->g(s[1], s[2], s[3]) + x[1] + 0xf61e2562, 5);
  s[3] = s[0] + edutls_rotl32(s[3] + this->g(s[0], s[1], s[2]) + x[6] + 0xc040b340, 9);
  s[2] = s[3] + edutls_rotl32(s[2] + this->g(s[3], s[0], s[1]) + x[11] + 0x265e5a51, 14);
  s[1] = s[2] + edutls_rotl32(s[1] + this->g(s[2], s[3], s[0]) + x[0] + 0xe9b6c7aa, 20);
  s[0] = s[1] + edutls_rotl32(s[0] + this->g(s[1], s[2], s[3]) + x[5] + 0xd62f105d, 5);
  s[3] = s[0] + edutls_rotl32(s[3] + this->g(s[0], s[1], s[2]) + x[10] + 0x02441453, 9);
  s[2] = s[3] + edutls_rotl32(s[2] + this->g(s[3], s[0], s[1]) + x[15] + 0xd8a1e681, 14);
  s[1] = s[2] + edutls_rotl32(s[1] + this->g(s[2], s[3], s[0]) + x[4] + 0xe7d3fbc8, 20);
  s[0] = s[1] + edutls_rotl32(s[0] + this->g(s[1], s[2], s[3]) + x[9] + 0x21e1cde6, 5);
  s[3] = s[0] + edutls_rotl32(s[3] + this->g(s[0], s[1], s[2]) + x[14] + 0xc33707d6, 9);
  s[2] = s[3] + edutls_rotl32(s[2] + this->g(s[3], s[0], s[1]) + x[3] + 0xf4d50d87, 14);
  s[1] = s[2] + edutls_rotl32(s[1] + this->g(s[2], s[3], s[0]) + x[8] + 0x455a14ed, 20);
  s[0] = s[1] + edutls_rotl32(s[0] + this->g(s[1], s[2], s[3]) + x[13] + 0xa9e3e905, 5);
  s[3] = s[0] + edutls_rotl32(s[3] + this->g(s[0], s[1], s[2]) + x[2] + 0xfcefa3f8, 9);
  s[2] = s[3] + edutls_rotl32(s[2] + this->g(s[3], s[0], s[1]) + x[7] + 0x676f02d9, 14);
  s[1] = s[2] + edutls_rotl32(s[1] + this->g(s[2], s[3], s[0]) + x[12] + 0x8d2a4c8a, 20);

  // Round 3
  s[0] = s[1] + edutls_rotl32(s[0] + this->h(s[1], s[2], s[3]) + x[5] + 0xfffa3942, 4);
  s[3] = s[0] + edutls_rotl32(s[3] + this->h(s[0], s[1], s[2]) + x[8] + 0x8771f681, 11);
  s[2] = s[3] + edutls_rotl32(s[2] + this->h(s[3], s[0], s[1]) + x[11] + 0x6d9d6122, 16);
  s[1] = s[2] + edutls_rotl32(s[1] + this->h(s[2], s[3], s[0]) + x[14] + 0xfde5380c, 23);
  s[0] = s[1] + edutls_rotl32(s[0] + this->h(s[1], s[2], s[3]) + x[1] + 0xa4beea44, 4);
  s[3] = s[0] + edutls_rotl32(s[3] + this->h(s[0], s[1], s[2]) + x[4] + 0x4bdecfa9, 11);
  s[2] = s[3] + edutls_rotl32(s[2] + this->h(s[3], s[0], s[1]) + x[7] + 0xf6bb4b60, 16);
  s[1] = s[2] + edutls_rotl32(s[1] + this->h(s[2], s[3], s[0]) + x[10] + 0xbebfbc70, 23);
  s[0] = s[1] + edutls_rotl32(s[0] + this->h(s[1], s[2], s[3]) + x[13] + 0x289b7ec6, 4);
  s[3] = s[0] + edutls_rotl32(s[3] + this->h(s[0], s[1], s[2]) + x[0] + 0xeaa127fa, 11);
  s[2] = s[3] + edutls_rotl32(s[2] + this->h(s[3], s[0], s[1]) + x[3] + 0xd4ef3085, 16);
  s[1] = s[2] + edutls_rotl32(s[1] + this->h(s[2], s[3], s[0]) + x[6] + 0x04881d05, 23);
  s[0] = s[1] + edutls_rotl32(s[0] + this->h(s[1], s[2], s[3]) + x[9] + 0xd9d4d039, 4);
  s[3] = s[0] + edutls_rotl32(s[3] + this->h(s[0], s[1], s[2]) + x[12] + 0xe6db99e5, 11);
  s[2] = s[3] + edutls_rotl32(s[2] + this->h(s[3], s[0], s[1]) + x[15] + 0x1fa27cf8, 16);
  s[1] = s[2] + edutls_rotl32(s[1] + this->h(s[2], s[3], s[0]) + x[2] + 0xc4ac5665, 23);

  // Round 4
  s[0] = s[1] + edutls_rotl32(s[0] + this->i(s[1], s[2], s[3]) + x[0] + 0xf4292244, 6);
  s[3] = s[0] + edutls_rotl32(s[3] + this->i(s[0], s[1], s[2]) + x[7] + 0x432aff97, 10);
  s[2] = s[3] + edutls_rotl32(s[2] + this->i(s[3], s[0], s[1]) + x[14] + 0xab9423a7, 15);
  s[1] = s[2] + edutls_rotl32(s[1] + this->i(s[2], s[3], s[0]) + x[5] + 0xfc93a039, 21);
  s[0] = s[1] + edutls_rotl32(s[0] + this->i(s[1], s[2], s[3]) + x[12] + 0x655b59c3, 6);
  s[3] = s[0] + edutls_rotl32(s[3] + this->i(s[0], s[1], s[2]) + x[3] + 0x8f0ccc92, 10);
  s[2] = s[3] + edutls_rotl32(s[2] + this->i(s[3], s[0], s[1]) + x[10] + 0xffeff47d, 15);
  s[1] = s[2] + edutls_rotl32(s[1] + this->i(s[2], s[3], s[0]) + x[1] + 0x85845dd1, 21);
  s[0] = s[1] + edutls_rotl32(s[0] + this->i(s[1], s[2], s[3]) + x[8] + 0x6fa87e4f, 6);
  s[3] = s[0] + edutls_rotl32(s[3] + this->i(s[0], s[1], s[2]) + x[15] + 0xfe2ce6e0, 10);
  s[2] = s[3] + edutls_rotl32(s[2] + this->i(s[3], s[0], s[1]) + x[6] + 0xa3014314, 15);
  s[1] = s[2] + edutls_rotl32(s[1] + this->i(s[2], s[3], s[0]) + x[13] + 0x4e0811a1, 21);
  s[0] = s[1] + edutls_rotl32(s[0] + this->i(s[1], s[2], s[3]) + x[4] + 0xf7537e82, 6);
  s[3] = s[0] + edutls_rotl32(s[3] + this->i(s[0], s[1], s[2]) + x[11] + 0xbd3af235, 10);
  s[2] = s[3] + edutls_rotl32(s[2] + this->i(s[3], s[0], s[1]) + x[2] + 0x2ad7d2bb, 15);
  s[1] = s[2] + edutls_rotl32(s[1] + this->i(s[2], s[3], s[0]) + x[9] + 0xeb86d391, 21);

  this->s[0] += s[0];
  this->s[1] += s[1];
  this->s[2] += s[2];
  this->s[3] += s[3];
}

void md5::digest(uint8_t *output) {
  for (this->b_len = 0; this->b_len < 4; this->b_len++) {
    output[(this->b_len * 4) + 0] = (uint8_t)(this->s[this->b_len] >> 0);
    output[(this->b_len * 4) + 1] = (uint8_t)(this->s[this->b_len] >> 8);
    output[(this->b_len * 4) + 2] = (uint8_t)(this->s[this->b_len] >> 16);
    output[(this->b_len * 4) + 3] = (uint8_t)(this->s[this->b_len] >> 24);
  }
}

void md5::init() {
  this->output_size = 16;
  this->le_padding = true;
  this->t_len = 0;
  this->b_len = 0;
  this->b_max = 64;

  this->block = new uint8_t[this->b_max];

  for (this->b_len = 0; this->b_len < this->b_max; this->b_len++) {
    this->block[this->b_len] = 0;
  }

  this->s[0] = 0x67452301;
  this->s[1] = 0xEFCDAB89;
  this->s[2] = 0x98BADCFE;
  this->s[3] = 0x10325476;

  this->b_len = 0;
}
