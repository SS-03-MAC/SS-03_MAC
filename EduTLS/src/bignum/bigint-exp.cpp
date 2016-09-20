//===-- EduTLS/src/bignum/bigint-exp.cc                   -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the BigInt modulus, exponentation
/// and modular exponentation functions.
///
//===----------------------------------------------------------------------===//

#include "bigint.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

BigInt *BigInt::mod(const BigInt *v) const {
  // Compute the modulus via integer division:
  // m = n - ((n/d)*d)
  BigInt *result;
  BigInt *num = new BigInt(this);
  BigInt *den = new BigInt(v);
  BigInt *m = num->div(den);
  BigInt *tmp = m->mul(den);
  result = num->sub(tmp);
  delete m;
  delete tmp;
  delete num;
  delete den;

  return result;
}

BigInt *BigInt::exp(const BigInt *v) {
  // Recursive exponentation:
  //    If even, compute (this^2)^(v/2)
  //    If odd, compute  this(this^2)^((v-1)/2).
  // Edge cases for zero and one.

  BigInt *result;
  BigInt *t = new BigInt(this);
  BigInt *val = new BigInt(v);
  BigInt *zero = new BigInt(0x00, false);
  BigInt *one = new BigInt(0x01, false);
  BigInt *two = new BigInt(0x02, false);

  if (val->equals(zero)) {
    result = new BigInt(0x01, false);
    delete t;
    delete val;
    delete zero;
    delete one;
    delete two;
    return result;
  }
  delete zero;

  if (val->equals(one)) {
    result = new BigInt(t);
    delete t;
    delete val;
    delete one;
    delete two;
    return result;
  }

  if (val->data->lsb() % 2 == 1) {
    BigInt *t2 = t->mul(t);

    BigInt *tmp = val->sub(one);
    BigInt *val2 = tmp->div(two);

    delete tmp;
    tmp = t2->exp(val2);

    result = tmp->mul(t);

    delete tmp;
    delete val2;
    delete t2;
  } else {
    BigInt *t2 = t->mul(t);
    BigInt *val2 = val->div(two);

    result = t2->exp(val2);

    delete t2;
    delete val2;
  }
  delete t;
  delete val;
  delete one;
  delete two;

  return result;
}

BigInt *BigInt::modexp(const BigInt *v, const BigInt *m) {
  // Recursive exponentation:
  //    If even, compute (this^2)^(v/2)
  //    If odd, compute  this(this^2)^((v-1)/2).
  // Edge cases for zero and one.
  // Same as exp except with internal moduli.

  BigInt *result;
  BigInt *t = new BigInt(this);
  BigInt *val = new BigInt(v);
  BigInt *mod = new BigInt(m);
  BigInt *zero = new BigInt(0x00, false);
  BigInt *one = new BigInt(0x01, false);
  BigInt *two = new BigInt(0x02, false);

  if (val->equals(zero)) {
    result = new BigInt(0x01, false);
    delete t;
    delete val;
    delete zero;
    delete one;
    delete two;
    delete mod;
    return result;
  }
  delete zero;

  if (val->equals(one)) {
    result = t->mod(mod);
    delete t;
    delete val;
    delete one;
    delete two;
    delete mod;
    return result;
  }

  if (val->data->lsb() % 2 == 1) {
    BigInt *t2 = t->mul(t);

    BigInt *tmp = val->sub(one);
    BigInt *val2 = tmp->div(two);

    delete tmp;
    tmp = t2->modexp(val2, mod);

    result = tmp->mul(t);

    delete tmp;
    delete val2;
    delete t2;
  } else {
    BigInt *t2 = t->mul(t);
    BigInt *val2 = val->div(two);

    result = t2->modexp(val2, mod);

    delete t2;
    delete val2;
  }
  delete t;
  delete val;
  delete one;
  delete two;

  BigInt *tmp = result->mod(mod);
  delete result;
  result = new BigInt(tmp);
  delete tmp;
  delete mod;

  return result;
}
