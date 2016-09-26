//===-- EduTLS/src/crypto/hash/sha2-512.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of SHA2-512, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "sha2-512.h"
#include "../utils.h"
#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

uint64_t sha2_512::ch(uint64_t x, uint64_t y, uint64_t z) { return (x & y) ^ ((~x) & z); }

uint64_t sha2_512::mj(uint64_t x, uint64_t y, uint64_t z) { return (x & y) ^ (x & z) ^ (y & z); }

uint64_t sha2_512::bsig0(uint64_t x) { return edutls_rotr32(x, 2) ^ edutls_rotr32(x, 13) ^ edutls_rotr32(x, 22); }

uint64_t sha2_512::bsig1(uint64_t x) { return edutls_rotr32(x, 6) ^ edutls_rotr32(x, 11) ^ edutls_rotr32(x, 25); }

uint64_t sha2_512::ssig0(uint64_t x) { return edutls_rotr32(x, 7) ^ edutls_rotr32(x, 18) ^ (x >> 3); }

uint64_t sha2_512::ssig1(uint64_t x) { return edutls_rotr32(x, 17) ^ edutls_rotr32(x, 19) ^ (x >> 10); }

void sha2_512::core() {

  size_t t = 0;
  uint64_t w[80];
  uint64_t h[8];
  uint64_t tmp1;
  uint64_t tmp2;

  static const uint64_t K[80] = {
      0x428A2F98D728AE22ll, 0x7137449123EF65CDll, 0xB5C0FBCFEC4D3B2Fll, 0xE9B5DBA58189DBBCll, 0x3956C25BF348B538ll,
      0x59F111F1B605D019ll, 0x923F82A4AF194F9Bll, 0xAB1C5ED5DA6D8118ll, 0xD807AA98A3030242ll, 0x12835B0145706FBEll,
      0x243185BE4EE4B28Cll, 0x550C7DC3D5FFB4E2ll, 0x72BE5D74F27B896Fll, 0x80DEB1FE3B1696B1ll, 0x9BDC06A725C71235ll,
      0xC19BF174CF692694ll, 0xE49B69C19EF14AD2ll, 0xEFBE4786384F25E3ll, 0x0FC19DC68B8CD5B5ll, 0x240CA1CC77AC9C65ll,
      0x2DE92C6F592B0275ll, 0x4A7484AA6EA6E483ll, 0x5CB0A9DCBD41FBD4ll, 0x76F988DA831153B5ll, 0x983E5152EE66DFABll,
      0xA831C66D2DB43210ll, 0xB00327C898FB213Fll, 0xBF597FC7BEEF0EE4ll, 0xC6E00BF33DA88FC2ll, 0xD5A79147930AA725ll,
      0x06CA6351E003826Fll, 0x142929670A0E6E70ll, 0x27B70A8546D22FFCll, 0x2E1B21385C26C926ll, 0x4D2C6DFC5AC42AEDll,
      0x53380D139D95B3DFll, 0x650A73548BAF63DEll, 0x766A0ABB3C77B2A8ll, 0x81C2C92E47EDAEE6ll, 0x92722C851482353Bll,
      0xA2BFE8A14CF10364ll, 0xA81A664BBC423001ll, 0xC24B8B70D0F89791ll, 0xC76C51A30654BE30ll, 0xD192E819D6EF5218ll,
      0xD69906245565A910ll, 0xF40E35855771202All, 0x106AA07032BBD1B8ll, 0x19A4C116B8D2D0C8ll, 0x1E376C085141AB53ll,
      0x2748774CDF8EEB99ll, 0x34B0BCB5E19B48A8ll, 0x391C0CB3C5C95A63ll, 0x4ED8AA4AE3418ACBll, 0x5B9CCA4F7763E373ll,
      0x682E6FF3D6B2B8A3ll, 0x748F82EE5DEFB2FCll, 0x78A5636F43172F60ll, 0x84C87814A1F0AB72ll, 0x8CC702081A6439ECll,
      0x90BEFFFA23631E28ll, 0xA4506CEBDE82BDE9ll, 0xBEF9A3F7B2C67915ll, 0xC67178F2E372532Bll, 0xCA273ECEEA26619Cll,
      0xD186B8C721C0C207ll, 0xEADA7DD6CDE0EB1Ell, 0xF57D4F7FEE6ED178ll, 0x06F067AA72176FBAll, 0x0A637DC5A2C898A6ll,
      0x113F9804BEF90DAEll, 0x1B710B35131C471Bll, 0x28DB77F523047D84ll, 0x32CAAB7B40C72493ll, 0x3C9EBE0A15C9BEBCll,
      0x431D67C49C100D4Cll, 0x4CC5D4BECB3E42B6ll, 0x597F299CFC657E2All, 0x5FCB6FAB3AD6FAECll, 0x6C44198C4A475817ll};

  for (t = 0; t < 16; t++) {
    w[t] = (((uint64_t)this->block[t * 8 + 0]) << 56) | (((uint64_t)this->block[t * 8 + 1]) << 48) |
           (((uint64_t)this->block[t * 8 + 2]) << 40) | (((uint64_t)this->block[t * 8 + 3]) << 32) |
           (((uint64_t)this->block[t * 8 + 4]) << 24) | (((uint64_t)this->block[t * 8 + 5]) << 16) |
           (((uint64_t)this->block[t * 8 + 6]) << 8) | (((uint64_t)this->block[t * 8 + 7]) << 0);
  }

  for (t = 16; t < 80; t++) {
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

  for (t = 0; t < 80; t++) {
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

void sha2_512::digest(uint8_t *output) {
  for (this->b_len = 0; this->b_len < 8; this->b_len++) {
    this->digest[(this->b_len * 8) + 0] = (uint8_t)(this->h[this->b_len] >> 56);
    this->digest[(this->b_len * 8) + 1] = (uint8_t)(this->h[this->b_len] >> 48);
    this->digest[(this->b_len * 8) + 2] = (uint8_t)(this->h[this->b_len] >> 42);
    this->digest[(this->b_len * 8) + 3] = (uint8_t)(this->h[this->b_len] >> 32);
    this->digest[(this->b_len * 8) + 4] = (uint8_t)(this->h[this->b_len] >> 24);
    this->digest[(this->b_len * 8) + 5] = (uint8_t)(this->h[this->b_len] >> 16);
    this->digest[(this->b_len * 8) + 6] = (uint8_t)(this->h[this->b_len] >> 8);
    this->digest[(this->b_len * 8) + 7] = (uint8_t)(this->h[this->b_len] >> 0);
  }
}

void sha2_512::init() {
  this->output_size = 64;
  this->le_padding = false;
  this->t_len = 0;
  this->b_len = 0;
  this->b_max = 128;

  this->block = new uint8_t[this->b_max];

  for (this->b_len = 0; this->b_len < this->b_max; this->b_len++) {
    this->block[this->b_len] = 0;
  }

  this->h[0] = 0x6a09e667f3bcc908ll;
  this->h[1] = 0xbb67ae8584caa73bll;
  this->h[2] = 0x3c6ef372fe94f82bll;
  this->h[3] = 0xa54ff53a5f1d36f1ll;
  this->h[4] = 0x510e527fade682d1ll;
  this->h[5] = 0x9b05688c2b3e6c1fll;
  this->h[6] = 0x1f83d9abfb41bd6bll;
  this->h[7] = 0x5be0cd19137e2179ll;

  this->b_len = 0;
}
