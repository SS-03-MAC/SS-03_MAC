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

  struct BigIntLLNode *a_curr = (struct BigIntLLNode *)this->data->tail;
  struct BigIntLLNode *b_curr = (struct BigIntLLNode *)val->data->tail;

  uint64_t carry = 0;
  int64_t add_result = 0;
  int64_t a_val = 0;
  int64_t b_val = 0;
  uint8_t len = 0;

  while (a_curr->prev != this->data->head && b_curr->prev != val->data->head) {
    a_curr = (struct BigIntLLNode *)a_curr->prev;
    b_curr = (struct BigIntLLNode *)b_curr->prev;

    a_val += ((uint64_t)a_curr->data) << (len * 8);
    b_val += ((uint64_t)b_curr->data) << (len * 8);

    len += 1;

    if (len == 7) {
      if (this->negative) {
        a_val *= -1;
      }

      if (val->negative) {
        b_val *= -1;
      }

      add_result = ((int64_t)carry) + a_val + b_val;
      if (add_result < 0) {
        add_result *= -1;
        result->negative = true;
      } else if (add_result > 0) {
        result->negative = false;
      }
      carry = (uint64_t)add_result;

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
      if (this->negative) {
        a_val *= -1;
      }

      if (val->negative) {
        b_val *= -1;
      }

      add_result = ((int64_t)carry) + a_val + b_val;
      if (add_result < 0) {
        add_result *= -1;
        result->negative = true;
      } else if (add_result > 0) {
        result->negative = false;
      }
      carry = (uint64_t)add_result;

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
      if (this->negative) {
        a_val *= -1;
      }

      if (val->negative) {
        b_val *= -1;
      }

      add_result = ((int64_t)carry) + a_val + b_val;
      if (add_result < 0) {
        add_result *= -1;
        result->negative = true;
      } else if (add_result > 0) {
        result->negative = false;
      }
      carry = (uint64_t)add_result;

      for (; len > 0; len--) {
        result->data->prepend((uint8_t)carry);
        carry = carry >> 8;
      }
      a_val = 0;
      b_val = 0;
      len = 0;
    }
  }

  if (len != 0) {
    if (this->negative) {
      a_val *= -1;
    }

    if (val->negative) {
      b_val *= -1;
    }

    add_result = ((int64_t)carry) + a_val + b_val;
    if (add_result < 0) {
      add_result *= -1;
      result->negative = true;
    } else if (add_result > 0) {
      result->negative = false;
    }
    carry = (uint64_t)add_result;

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

  val->negate();
  result = t->add(val);
  val->negate();

  delete val;
  delete t;

  return result;
}
