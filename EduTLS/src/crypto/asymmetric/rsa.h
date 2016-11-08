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

#pragma once

#include "../../bignum/bigint.h"

#include <cstddef>
#include <cstdint>
#include <gmp.h>

#define PUBLIC_KEY 1
#define PRIVATE_KEY 2

class rsa {
private:
  mpz_t n;
  mpz_t e;
  mpz_t d;
  mpz_t p;
  mpz_t q;

  uint16_t bits;

  int type;

  void gen_modulus();

public:
  void encrypt(mpz_t output, mpz_t input);
  void decrypt(mpz_t output, mpz_t input);
  void sign(mpz_t output, mpz_t input);
  void verify(mpz_t output, mpz_t input);

  void exponent(mpz_t e);
  void priv(mpz_t d);
  void priv(mpz_t p, mpz_t q);
  void modulus(mpz_t n);

  int get_types();

  rsa();
  rsa(mpz_t p, mpz_t q, mpz_t e);
  ~rsa();
};
