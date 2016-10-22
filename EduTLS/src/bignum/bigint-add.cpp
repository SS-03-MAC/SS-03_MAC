//===-- EduTLS/src/bignum/bigint-add.cc                   -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the BigInt addition and
/// subtraction methods. Subtraction is addition with a negated second
/// parameter.
///
//===----------------------------------------------------------------------===//

#include "bigint.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

BigInt *BigInt::add(const BigInt *val) {
  BigInt *result = new BigInt();


  if (this->negative != val->negative) {
    if (this->negative) {
      BigInt *cpy = new BigInt(val);
      this->negate();
      BigInt *data = cpy->sub(this);
      result->copy(data);
      this->negate();

      delete cpy;
      delete data;
    } else {
      BigInt *cpy = new BigInt(val);
      cpy->negate();
      BigInt *data = this->sub(cpy);
      result->copy(data);

      delete cpy;
      delete data;
    }
    return result;
  }

  result->negative = this->negative;

  struct BigIntLLNode *a_curr = (struct BigIntLLNode *)this->data->tail;
  struct BigIntLLNode *b_curr = (struct BigIntLLNode *)val->data->tail;

  uint64_t carry = 0;
  uint64_t a_val = 0;
  uint64_t b_val = 0;
  size_t len = 0;

  // Starting at the LSB, group into sets of 7 bytes and perform addition,
  // saving the carry bit. Perform addition as signed integers, allowing the
  // sign of the result to be determined during calculations.
  //
  // Once finished, the remaining number can be added verbatim, keeping the
  // previous carry as necessary.

  while (a_curr->prev != this->data->head && b_curr->prev != val->data->head) {
    a_curr = (struct BigIntLLNode *)a_curr->prev;
    b_curr = (struct BigIntLLNode *)b_curr->prev;

    a_val += ((uint64_t)a_curr->data) << (len * 8);
    b_val += ((uint64_t)b_curr->data) << (len * 8);

    len += 1;

    if (len == 7) {
      carry = carry + a_val + b_val;

      for (; len > 0; len--) {
        result->data->prepend((uint8_t)carry);
        carry = carry >> 8;
      }
      a_val = 0;
      b_val = 0;
      len = 0;
    }
  }

  while (a_curr->prev != this->data->head) {
    a_curr = (struct BigIntLLNode *)a_curr->prev;

    a_val += ((uint64_t)a_curr->data) << (len * 8);
    b_val += 0;

    len += 1;

    if (len == 7) {
      carry = carry + a_val + b_val;

      for (; len > 0; len--) {
        result->data->prepend((uint8_t)carry);
        carry = carry >> 8;
      }
      a_val = 0;
      b_val = 0;
      len = 0;
    }
  }

  while (b_curr->prev != val->data->head) {
    b_curr = (struct BigIntLLNode *)b_curr->prev;

    a_val += 0;
    b_val += ((uint64_t)b_curr->data) << (len * 8);

    len += 1;

    if (len == 7) {
      carry = carry + a_val + b_val;

      for (; len > 0; len--) {
        result->data->prepend((uint8_t)carry);
        carry = carry >> 8;
      }
      a_val = 0;
      b_val = 0;
      len = 0;
    }
  }

  // At the end, deal with any remaining data.
  if (len != 0) {
    carry = carry + a_val + b_val;

    for (; len > 0; len--) {
      result->data->prepend((uint8_t)carry);
      carry = carry >> 8;
    }
    a_val = 0;
    b_val = 0;
    len = 0;
  }

  while (carry != 0) {
    result->data->prepend((uint8_t)carry);
    carry = carry >> 8;
  }

  return result;
}

BigInt *BigInt::sub(const BigInt *v) {
  BigInt *result;
  BigInt *val = new BigInt(v);
  BigInt *t = new BigInt(this);

  if (this->negative || v->negative) {
    val->negate();
    result = t->add(val);
    val->negate();

    delete val;
    delete t;

    return result;
  }

  if (this->cmp(val) < 0) {
    result = val->sub(t);
    result->negative = true;

    delete val;
    delete t;

    return result;
  }

  int borrow;
  int digit;

  

  delete val;
  delete t;

  return result;
}
