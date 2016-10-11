//===-- EduTLS/src/crypto/asymmetric/rsa.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the RSA class for use with asymmetric
/// encryption.
///
//===----------------------------------------------------------------------===//

#include "../../bignum/bigint.h"

#include <cstddef>
#include <cstdint>

#pragma once

#define PUBLIC_KEY 1
#define PRIVATE_KEY 2

class rsa {
private:
  BigInt *n;
  BigInt *e;
  BigInt *d;
  BigInt *p;
  BigInt *q;

  uint16_t bits;

  int type;

  void gen_modulus();

public:
  void encrypt(BigInt *output, BigInt *input);
  void decrypt(BigInt *output, BigInt *input);
  void sign(BigInt *output, BigInt *input);
  void verify(BigInt *output, BigInt *input);

  void exponent(BigInt *e);
  void priv(BigInt *d);
  void priv(BigInt *p, BigInt *q);
  void modulus(BigInt *n);

  int get_types();

  rsa();
  rsa(BigInt *p, BigInt *q, BigInt *e);
  ~rsa();
};
