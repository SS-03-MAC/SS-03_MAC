//===-- EduTLS/src/bignum/bigint.h                        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the BigInt class for use with
/// number theoretic cryptography such as RSA and ECC.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "bigint_ll.h"

class BigInt {
private:
  bool negative;
  BigIntLL *data;

public:
  /// Default constructor to initialize to implicit zero.
  BigInt();

  /// Constructor initializes to a uint64_t value, setting negative if true.
  BigInt(uint64_t val, bool negative);

  /// Constructor from a set of uint8_t data chunks; lowest index is most
  /// significant byte.
  BigInt(bool negative, const uint8_t *val, uint64_t length);

  /// Copy constructor duplicates data from *val.
  BigInt(const BigInt *val);

  /// Destructor.
  ~BigInt() { delete data; }

  /// Copy into an already initialized BigInt.
  void copy(const BigInt *val);

  /// Prints the BigInt with most significant byte first.
  void print() const;

  /// Prints the BigInt with least significant byte first.
  void rev_print() const;

  /// Comparision between two BigInt.
  int cmp(const BigInt *val) const;

  /// Equality check
  bool equals(const BigInt *val) const { return (this->cmp(val) == 0); }

  /// Left shift operator.
  void left_shift(uint64_t amount);

  /// Right shift operator.
  void right_shift(uint64_t amount);

  /// Performs addition of $this + val$.
  BigInt *add(const BigInt *val);

  /// Negates the number.
  void negate() { this->negative = !this->negative; }

  /// Performs subtraction of $this - v$.
  BigInt *sub(const BigInt *v);

  /// Performs multiplication of $this * v$.
  BigInt *mul(const BigInt *v) const;

  /// Performs division of $this / v$.
  BigInt *div(const BigInt *v) const;

  /// Performs r = GCD(this, y), where r is the return value and a and b are
  /// Bezout's constants.
  BigInt *egcd(const BigInt *y, BigInt *a, BigInt *b) const;

  /// Modular inverse of this over the field m.
  BigInt *modinv(const BigInt *m);

  /// Performs modulus of $this % v$.
  BigInt *mod(const BigInt *v) const;

  /// Exponentiation of $this ^ v$.
  BigInt *exp(const BigInt *v);

  /// Modular exponentiation of $this ^ v % m$.
  BigInt *modexp(const BigInt *v, const BigInt *m);

  /// Remove leading zero bytes.
  void trim() { this->data->trim(); }
};
