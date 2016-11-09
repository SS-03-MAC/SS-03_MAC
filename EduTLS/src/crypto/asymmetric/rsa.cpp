//===-- EduTLS/src/crypto/asymmetric/rsa.cpp              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the RSA class for use with
/// asymmetric encryption.
///
//===----------------------------------------------------------------------===//

#include "rsa.h"
#include <gmp.h>

rsa::rsa() {
  mpz_init(this->n);
  mpz_init(this->e);
  mpz_init(this->d);
  mpz_init(this->p);
  mpz_init(this->q);
  this->type = 0;
}

rsa::rsa(mpz_t p, mpz_t q, mpz_t e) {
  mpz_init(this->n);
  mpz_init_set(this->e, e);
  mpz_init(this->d);
  mpz_init_set(this->p, p);
  mpz_init_set(this->q, q);

  this->type = PUBLIC_KEY | PRIVATE_KEY;
}

rsa::~rsa() {
  mpz_clear(this->n);
  mpz_clear(this->e);
  mpz_clear(this->d);
  mpz_clear(this->p);
  mpz_clear(this->q);
}

void rsa::encrypt(mpz_t output, mpz_t input) {
  if (mpz_cmp(this->n, input) <= 0) {
    throw - 1;
  }

  mpz_powm(output, input, this->e, this->n);
}

void rsa::decrypt(mpz_t output, mpz_t input) {
  if (mpz_cmp(this->n, input) <= 0) {
    throw - 1;
  }

  mpz_powm(output, input, this->d, this->n);
}

void rsa::sign(mpz_t output, mpz_t input) {
  if (mpz_cmp(this->n, input) <= 0) {
    throw - 1;
  }

  mpz_powm(output, input, this->d, this->n);
}

void rsa::verify(mpz_t output, mpz_t input) {
  if (mpz_cmp(this->n, input) <= 0) {
    throw - 1;
  }

  mpz_powm(output, input, this->e, this->n);
}

int rsa::get_types() { return this->type; }

void rsa::exponent(mpz_t e) {
  mpz_clear(this->e);
  mpz_init_set(this->e, e);
  this->type = this->type | PUBLIC_KEY;
}

void rsa::priv(mpz_t d) {
  mpz_clear(this->d);
  mpz_init_set(this->d, d);
  this->type = this->type | PRIVATE_KEY;
}

void rsa::priv(mpz_t p, mpz_t q) {
  mpz_clear(this->p);
  mpz_init_set(this->p, p);
  mpz_clear(this->q);
  mpz_init_set(this->q, q);
  this->type = PUBLIC_KEY | PRIVATE_KEY;
}

void rsa::modulus(mpz_t n) {
  mpz_clear(this->n);
  mpz_init_set(this->n, n);
}
