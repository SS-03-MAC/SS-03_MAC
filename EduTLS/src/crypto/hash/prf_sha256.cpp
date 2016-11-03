//===-- EduTLS/src/crypto/hash/prf_sha256.cpp             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the PRF SHA256 construction.
///
//===----------------------------------------------------------------------===//

#include "./prf_sha256.h"
#include "../utils.h"
#include "./hash.h"
#include "./hmac.h"
#include "./sha2-256.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

prf_sha256::prf_sha256(uint8_t *secret, size_t secret_length, uint8_t *seed, size_t seed_length) {
  this->secret = (uint8_t *)malloc(sizeof(uint8_t) * secret_length);
  this->secret_length = secret_length;
  memcpy(this->secret, secret, secret_length);

  this->seed = (uint8_t *)malloc(sizeof(uint8_t) * seed_length);
  this->seed_length = seed_length;
  memcpy(this->seed, seed, seed_length);

  this->hasher.init();
  this->h = new hmac(&this->hasher, this->secret, this->secret_length);
}

prf_sha256::~prf_sha256() {
  delete this->h;
  free(this->secret);
  free(this->seed);
}

void prf_sha256::generate(uint8_t *output, size_t length) {
  size_t o_p = 0;
  size_t O_p = 0;

  uint8_t A[this->h->output_size];
  uint8_t O[this->h->output_size];
  this->h->sum(A, this->seed, this->seed_length);
  this->h->init();
  this->h->update(A, this->h->output_size);
  this->h->update(this->seed, this->seed_length);
  this->h->finalize(O);

  for (o_p = 0; o_p < length; o_p++) {
    output[o_p] = O[O_p];
    O_p += 1;
    if (O_p == this->h->output_size) {
      O_p = 0;
      this->h->sum(A, A, this->h->output_size);
      this->h->init();
      this->h->update(A, this->h->output_size);
      this->h->update(this->seed, this->seed_length);
      this->h->finalize(O);
    }
  }
}
