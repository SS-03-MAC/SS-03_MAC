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

rsa::rsa() {
  this->n = new BigInt();
  this->e = new BigInt();
  this->d = new BigInt();
  this->p = new BigInt();
  this->q = new BigInt();
  this->type = 0;
}

rsa::rsa(BigInt *p, BigInt *q, BigInt *e) {
  this->n = new BigInt();
  this->e = new BigInt();
  this->d = new BigInt();
  this->p = new BigInt();
  this->q = new BigInt();

  this->p->copy(p);
  this->q->copy(q);
  this->e->copy(e);
  this->type = PUBLIC_KEY | PRIVATE_KEY;
}

rsa::~rsa() {
  delete this->n;
  delete this->e;
  delete this->d;
  delete this->p;
  delete this->q;
}

void rsa::encrypt(BigInt *output, BigInt *input) {
  if (this->n->cmp(input) <= 0) {
    throw - 1;
  }

  BigInt *result = input->modexp(this->e, this->n);
  output->copy(result);
}

void rsa::decrypt(BigInt *output, BigInt *input) {
  if (this->n->cmp(input) <= 0) {
    throw - 1;
  }

  BigInt *result = input->modexp(this->d, this->n);
  output->copy(result);
}

void rsa::sign(BigInt *output, BigInt *input) {
  if (this->n->cmp(input) <= 0) {
    throw - 1;
  }

  BigInt *result = input->modexp(this->d, this->n);
  output->copy(result);
}

void rsa::verify(BigInt *output, BigInt *input) {
  if (this->n->cmp(input) <= 0) {
    throw - 1;
  }

  BigInt *result = input->modexp(this->e, this->n);
  output->copy(result);
}

int rsa::get_types() { return this->type; }

void rsa::exponent(BigInt *e) {
  this->e->copy(e);
  this->type = this->type | PUBLIC_KEY;
}

void rsa::priv(BigInt *d) {
  this->d->copy(d);
  this->type = this->type | PRIVATE_KEY;
}

void rsa::priv(BigInt *p, BigInt *q) {
  this->q->copy(p);
  this->p->copy(q);
  this->type = PUBLIC_KEY | PRIVATE_KEY;
}

void rsa::modulus(BigInt *n) { this->n->copy(n); }
