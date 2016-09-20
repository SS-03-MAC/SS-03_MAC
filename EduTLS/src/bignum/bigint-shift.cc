//===-- EduTLS/src/bignum/bigint.cc                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the BigInt left and right shift
/// functions.
///
//===----------------------------------------------------------------------===//

#include "bigint.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

void BigInt::left_shift(uint64_t amount) {
  uint64_t times = 0;
  uint64_t bytes = amount / 8;
  uint8_t shift = (uint8_t)(amount % 8);
  struct BigIntLLNode *curr;
  struct BigIntLLNode *next;
  uint8_t next_mask = ((1 << shift) - 1);
  uint8_t data_mask = (0xFF << shift);

  // Shifting by a multiple of 8 is linear in magnitude of multiple.
  // Anything else requires iterating over the linked list using masks and shifting.

  this->data->trim();

  this->data->prepend(0x00);

  for (times = 0; times < bytes; times++) {
    this->data->append(0x00);
  }

  curr = (struct BigIntLLNode *)(this->data->head->next);
  next = (struct BigIntLLNode *)(curr->next);

  if (curr == this->data->tail || shift == 0) {
    return;
  }

  this->data->rotl_each(shift);

  while (next != (struct BigIntLLNode *)data->tail) {
    curr->data = (curr->data & data_mask) ^ (next->data & next_mask);

    curr = next;
    next = (struct BigIntLLNode *)(curr->next);
  }
  curr->data = (curr->data & data_mask);

  this->data->trim();
}

void BigInt::right_shift(uint64_t amount) {
  uint64_t times = 0;
  uint64_t bytes = amount / 8;
  uint8_t shift = (uint8_t)(amount % 8);

  struct BigIntLLNode *curr;
  struct BigIntLLNode *next;

  if (((struct BigIntLLNode *)this->data->tail->prev) == this->data->head || amount == 0) {
    return;
  }

  uint8_t data_mask = (0xFF >> shift);
  uint8_t next_mask = 0xFF - data_mask;

  // Shifting by a multiple of 8 is linear in magnitude of multiple.
  // Anything else requires iterating over the linked list using masks and shifting.

  this->data->trim();

  for (times = 0; times < bytes; times++) {
    this->data->remove_last();
  }

  if (shift == 0) {
    return;
  }

  this->data->prepend(0x00);

  curr = (struct BigIntLLNode *)(this->data->tail->prev);
  next = (struct BigIntLLNode *)(curr->prev);

  this->data->rotr_each(shift);

  while (next != data->head) {
    curr->data = (curr->data & data_mask) ^ (next->data & next_mask);

    curr = next;
    next = (struct BigIntLLNode *)(curr->prev);
  }
  curr->data = (curr->data & data_mask);

  this->data->trim();
}
