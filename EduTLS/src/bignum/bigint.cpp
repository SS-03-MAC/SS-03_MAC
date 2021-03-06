//===-- EduTLS/src/bignum/bigint.cc                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the BigInt constructors and other
/// utility functions which are non-mathematical in nature.
///
//===----------------------------------------------------------------------===//

#include "bigint.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

BigInt::BigInt() {
  data = new BigIntLL();
  this->negative = false;
}

BigInt::BigInt(uint64_t val, bool negative) {
  this->negative = negative;
  data = new BigIntLL(val);
}

BigInt::BigInt(bool negative, const uint8_t *val, uint64_t length) {
  uint64_t i = 0;
  this->negative = negative;
  this->data = new BigIntLL();

  // Least index is first.
  for (i = 0; i < length; i++) {
    this->data->append(val[i]);
  }
}

BigInt::BigInt(const BigInt *val) {
  this->negative = val->negative;
  this->data = new BigIntLL(val->data);
}

void BigInt::copy(const BigInt *val) {
  this->negative = val->negative;
  delete this->data;
  this->data = new BigIntLL(val->data);
}

void BigInt::print() const {
  if (!this->negative) {
    printf("+");
  } else {
    printf("-");
  }

  this->data->print();

  printf("\n");
}

void BigInt::rev_print() const {
  this->data->rev_print();

  if (!this->negative) {
    printf("+");
  } else {
    printf("-");
  }

  printf("\n");
}

int BigInt::cmp(const BigInt *val) const {
  uint64_t t_l = this->data->non_zero_length();
  uint64_t v_l = val->data->non_zero_length();
  struct BigIntLLNode *t_c;
  struct BigIntLLNode *v_c;
  t_c = (struct BigIntLLNode *)(this->data->head)->next;
  v_c = (struct BigIntLLNode *)(val->data->head)->next;

  /// If both lengths are zero, both values must be zero.
  if (t_l == v_l && t_l == 0) {
    return 0;
  }

  if (val->negative != this->negative) {
    if (this->negative) {
      return -1;
    } else {
      return 1;
    }
  }

  if (t_l > v_l) {
    return 1;
  } else if (t_l < v_l) {
    return -1;
  }

  // Find the first non-zero element in this.
  while (t_c != this->data->tail && t_c->data == 0x00) {
    t_c = (struct BigIntLLNode *)t_c->next;
  }

  // Find the first non-zero element in val.
  while (v_c != val->data->tail && v_c->data == 0x00) {
    v_c = (struct BigIntLLNode *)v_c->next;
  }

  // Starting at the MSB, find first differing element and return.
  while (t_c != this->data->tail && v_c != val->data->tail) {
    if (t_c->data > v_c->data) {
      return 1;
    } else if (t_c->data < v_c->data) {
      return -1;
    }

    t_c = (struct BigIntLLNode *)t_c->next;
    v_c = (struct BigIntLLNode *)v_c->next;
  }

  return 0;
}

size_t BigInt::bytes(uint8_t *data) {
  struct BigIntLLNode *curr;
  curr = (struct BigIntLLNode *)(this->data->head)->next;

  // Ingore leading zeros
  while (curr != this->data->tail) {
    if (curr->data != 0x00) {
      break;
    }

    curr = (struct BigIntLLNode *)curr->next;
  }

  size_t d_p = 0;
  if (curr == this->data->tail) {
    data[0] = 0;
    return 1;
  }

  while (curr != this->data->tail) {
    data[d_p] = curr->data;

    curr = (struct BigIntLLNode *)curr->next;
    d_p += 1;
  }

  return d_p;
}
