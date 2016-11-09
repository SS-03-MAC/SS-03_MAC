//===-- EduTLS/src/crypto/asymmetric/dh.cpp               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the DH class for use with
/// key exchange.
///
//===----------------------------------------------------------------------===//

#include "dh.h"

dh::dh() {
  this->x = new BigInt();
  this->y = new BigInt();
  this->p = new BigInt();
  this->q = new BigInt();
  this->g = new BigInt();
  this->h = new BigInt();
  this->j = new BigInt();
}

dh::dh(BigInt *x, BigInt *y) {
  this->x = new BigInt();
  this->y = new BigInt();
  this->p = new BigInt();
  this->q = new BigInt();
  this->g = new BigInt();
  this->h = new BigInt();
  this->j = new BigInt();

  this->x->copy(x);
  this->y->copy(y);
}

dh::~dh() {
  delete this->x;
  delete this->y;
  delete this->p;
  delete this->q;
  delete this->g;
  delete this->h;
  delete this->j;
}

void dh::compute(BigInt *output, BigInt *input) {
  BigInt *result = input->modexp(this->x, this->p);
  output->copy(result);
}

void dh::pub(BigInt *x) { this->x->copy(x); }
void dh::priv(BigInt *y) { this->y->copy(y); }
void dh::primes(BigInt *p, BigInt *q) {

  this->p->copy(p);
  this->q->copy(q);
}
void dh::generator(BigInt *g) { this->g->copy(g); }
