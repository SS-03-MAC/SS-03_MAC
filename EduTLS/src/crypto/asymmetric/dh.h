//===-- EduTLS/src/crypto/asymmetric/dh.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the DH class for use with key
/// exchange.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../../bignum/bigint.h"

#include <cstddef>
#include <cstdint>

class dh {
private:
  BigInt *x;
  BigInt *y;
  BigInt *p;
  BigInt *q;
  BigInt *g;
  BigInt *h;
  BigInt *j;

public:
  void compute(BigInt *output, BigInt *input);

  void pub(BigInt *x);
  void priv(BigInt *y);
  void primes(BigInt *p, BigInt *q);
  void generator(BigInt *g);

  dh();
  dh(BigInt *x, BigInt *y);
  ~dh();
};
