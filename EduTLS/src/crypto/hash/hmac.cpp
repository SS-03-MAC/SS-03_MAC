//===-- EduTLS/src/crypto/hash/hmac.cpp                   -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the HMAC construction.
///
//===----------------------------------------------------------------------===//

#include "./hmac.h"
#include "../utils.h"
#include "./hash.h"
#include <cstdio>
#include <cstdlib>

hmac::hmac(hash *h, uint8_t *key, size_t key_length) {
  size_t i = 0;
  this->h = h;
  this->block_size = h->block_size;
  this->output_size = h->output_size;

  this->ipad = (uint8_t *)malloc(sizeof(uint8_t) * block_size);
  this->opad = (uint8_t *)malloc(sizeof(uint8_t) * block_size);
  this->key = (uint8_t *)malloc(sizeof(uint8_t) * block_size);
  for (i = 0; i < block_size; i++) {
    this->ipad[i] = 0x36;
    this->opad[i] = 0x5C;
    this->key[i] = 0x00;
  }

  if (key_length > block_size) {
    h->sum(this->key, key, key_length);
  } else {
    for (i = 0; i < key_length; i++) {
      this->key[i] = key[i];
    }
  }

  edutls_xor(this->ipad, this->ipad, this->key, block_size);
  edutls_xor(this->opad, this->opad, this->key, block_size);
}

hmac::~hmac() {
  free(this->ipad);
  free(this->opad);
  free(this->key);

  delete this->h;
}

void hmac::init() {

  this->h->init();
  this->h->update(this->ipad, this->block_size);
}
void hmac::update(uint8_t *input, size_t count) { this->h->update(input, count); }

void hmac::finalize(uint8_t *output) {
  uint8_t intermediate[this->output_size];

  this->h->finalize(intermediate);
  this->h->init();
  this->h->update(this->opad, this->block_size);
  this->h->update(intermediate, this->output_size);
  this->h->finalize(output);
}
