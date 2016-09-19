/*
 * Bignum library
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#pragma once
#ifndef BIGNUM_SRC_LIB_BIGINT_H__
#define BIGNUM_SRC_LIB_BIGINT_H__

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
  BigInt();

  BigInt(uint64_t val, bool negative);

  BigInt(bool negative, const uint8_t *val, uint64_t length);

  BigInt(const BigInt *val);

  ~BigInt() { delete data; }

  void print() const;

  void rev_print() const;

  int cmp(const BigInt *val);

  bool equals(const BigInt *val) { return (this->cmp(val) == 0); }

  void left_shift(uint64_t amount);

  void right_shift(uint64_t amount);

  BigInt *add(const BigInt *val);

  void negate() { this->negative = !this->negative; }

  BigInt *sub(const BigInt *v);

  BigInt *mul(const BigInt *v) const;

  BigInt *div(const BigInt *v) const;

  BigInt *egcd(const BigInt *y, BigInt *a, BigInt *b) const;

  BigInt *modinv(const BigInt *m);

  BigInt *mod(const BigInt *v) const;

  BigInt *exp(const BigInt *v);

  BigInt *modexp(const BigInt *v, const BigInt *m);

  BigInt *gcd(const BigInt *b, const BigInt *r, const BigInt *s);

  void trim() { this->data->trim(); }
};

#endif /* end of include guard: BIGNUM_SRC_LIB_BIGINT_H__ */
