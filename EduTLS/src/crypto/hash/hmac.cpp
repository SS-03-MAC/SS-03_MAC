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
  this->block_length = h->block_size;
  this->output_length = h->output_size;

  this->ipad = (uint8_t *)malloc(sizeof(uint8_t) * block_length);
  this->opad = (uint8_t *)malloc(sizeof(uint8_t) * block_length);
  this->key = (uint8_t *)malloc(sizeof(uint8_t) * block_length);
  for (i = 0; i < block_length; i++) {
    this->ipad[i] = 0x36;
    this->opad[i] = 0x5C;
    this->key[i] = 0x00;
  }

  if (key_length > block_length) {
    h->sum(this->key, key, key_length);
  } else {
    for (i = 0; i < key_length; i++) {
      this->key[i] = key[i];
    }
  }

  edutls_xor(this->ipad, this->ipad, this->key, block_length);
  edutls_xor(this->opad, this->opad, this->key, block_length);
}

hmac::~hmac() {
  free(this->ipad);
  free(this->opad);
  free(this->key);
}

void hmac::sum(uint8_t *result, uint8_t *text, size_t text_length) {
  uint8_t intermediate[this->output_length];
  this->h->init();
  this->h->update(this->ipad, this->block_length);
  this->h->update(text, text_length);
  this->h->finalize(intermediate);
  this->h->init();
  this->h->update(this->opad, this->block_length);
  this->h->update(intermediate, this->output_length);
  this->h->finalize(result);
}
