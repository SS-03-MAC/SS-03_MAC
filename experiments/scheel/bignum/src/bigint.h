/*
 * Bignum library
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "bigint_ll.h"

class BigInt {
private:
  bool negative;
  BigIntLL data;

public:
  BigInt() {
    data = BigIntLL();
    this->negative = false;
  }

  BigInt(uint64_t val) {
    this->negative = false;
    data = BigIntLL(val);
  }

  BigInt(const BigInt &val) {
    this->negative = val.negative;
    this->data = BigIntLL(val.data);
  }

  void print() {
    if (!this->negative) {
      printf("+");
    } else {
      printf("-");
    }

    this->data.print();

    printf("\n");
  }

  void rev_print() {
    this->data.rev_print();

    if (!this->negative) {
      printf("+");
    } else {
      printf("-");
    }

    printf("\n");
  }

  void left_shift(uint64_t amount) {
    uint64_t times = 0;
    uint64_t bytes = amount / 8;
    uint64_t shift = amount % 8;

    this->data.prepend(0x00);

    for (times = 0; times < bytes; times++) {
      this->data.append(0x00);
    }

    // TODO, finish shift
    this->data.rotl_each(shift);
  }

  BigInt add(const BigInt &val) {
    BigInt result = BigInt();

    struct BigIntLLNode *a_curr = (struct BigIntLLNode *)this->data.tail;
    struct BigIntLLNode *b_curr = (struct BigIntLLNode *)val.data.tail;

    uint64_t carry = 0;
    uint64_t a_val = 0;
    uint64_t b_val = 0;
    uint8_t len = 0;

    while (a_curr->prev != this->data.head && b_curr->prev != val.data.head) {
      a_curr = (struct BigIntLLNode *)a_curr->prev;
      b_curr = (struct BigIntLLNode *)b_curr->prev;

      a_val += ((uint64_t)a_curr->data) << (len * 8);
      b_val += ((uint64_t)b_curr->data) << (len * 8);

      len += 1;

      if (len == 4) {
        carry = carry + a_val + b_val;
        for (; len > 0; len--) {
          result.data.prepend((uint8_t)carry);
          carry = carry >> 8;
        }
        a_val = 0;
        b_val = 0;
        len = 0;
      }
    }

    while (a_curr->prev != this->data.head) {
      a_curr = (struct BigIntLLNode *)a_curr->prev;

      a_val += ((uint64_t)a_curr->data) << (len * 8);
      b_val += 0;

      len += 1;

      if (len == 4) {
        carry = carry + a_val + b_val;
        for (; len > 0; len--) {
          result.data.prepend((uint8_t)carry);
          carry = carry >> 8;
        }
        a_val = 0;
        b_val = 0;
        len = 0;
      }
    }

    while (b_curr->prev != val.data.head) {
      b_curr = (struct BigIntLLNode *)b_curr->prev;

      a_val += 0;
      b_val += ((uint64_t)b_curr->data) << (len * 8);

      len += 1;

      if (len == 4) {
        carry = carry + a_val + b_val;
        for (; len > 0; len--) {
          result.data.prepend((uint8_t)carry);
          carry = carry >> 8;
        }
        a_val = 0;
        b_val = 0;
        len = 0;
      }
    }

    if (len != 0) {
      carry = carry + a_val + b_val;
      for (; len > 0; len--) {
        result.data.prepend((uint8_t)carry);
        carry = carry >> 8;
      }
      a_val = 0;
      b_val = 0;
      len = 0;
    }

    while (carry != 0) {
      result.data.prepend((uint8_t)carry);
      carry = carry >> 8;
    }

    return result;
  }

  void subtract() { this->data.prepend(0x40); }

  // void add(const BigInt &val) {}

  // void shift(uint64_t bits) {}
};
