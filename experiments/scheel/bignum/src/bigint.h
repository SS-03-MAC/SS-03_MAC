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
  BigIntLL *data;

public:
  BigInt() {
    data = new BigIntLL();
    this->negative = false;
  }

  BigInt(uint64_t val) {
    this->negative = false;
    data = new BigIntLL(val);
  }

  BigInt(const BigInt *val) {
    this->negative = val->negative;
    this->data = new BigIntLL(val->data);
  }

  ~BigInt() { delete data; }

  void print() const {
    if (!this->negative) {
      printf("+");
    } else {
      printf("-");
    }

    this->data->print();

    printf("\n");
  }

  void rev_print() const {
    this->data->rev_print();

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
    struct BigIntLLNode *curr = (struct BigIntLLNode *)(this->data->head->next);
    struct BigIntLLNode *next = (struct BigIntLLNode *)(curr->next);
    uint8_t next_mask = ((1 << amount) - 1);
    uint8_t data_mask = (0xFF << amount);

    this->data->trim();

    this->data->prepend(0x00);

    for (times = 0; times < bytes; times++) {
      printf("Adding 8 bits...\n");
      this->print();
      this->rev_print();
      this->data->append(0x00);
      this->rev_print();
      this->print();
    }

    this->data->rotl_each(shift);
    while (curr->next != data->tail) {
      curr->data = (curr->data & data_mask) ^ next->data & next_mask;

      curr = next;
      next = (struct BigIntLLNode *)(curr->next);
    }
    curr->data = (curr->data & data_mask);

    this->data->trim();
  }

  void right_shift(uint64_t amount) {
    uint64_t times = 0;
    uint64_t bytes = amount / 8;
    uint64_t shift = amount % 8;

    struct BigIntLLNode *curr = (struct BigIntLLNode *)(this->data->tail->prev);
    struct BigIntLLNode *next = (struct BigIntLLNode *)(curr->prev);

    uint8_t next_mask = (0xFF << amount);
    uint8_t data_mask = ((1 << amount) - 1);

    for (times = 0; times < bytes; times++) {
      this->data->remove_last();
    }

    this->data->rotr_each(shift);
    while (curr->prev != data->head) {
      curr->data = (curr->data & data_mask) ^ next->data & next_mask;

      curr = next;
      next = (struct BigIntLLNode *)(curr->prev);
    }
    curr->data = (curr->data & data_mask);

    this->data->trim();
  }

  BigInt *add(const BigInt *val) {
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

  void negate() { this->negative = !this->negative; }

  BigInt *subtract(BigInt *val) {
    BigInt *result;

    val->negate();
    result = this->add(val);
    val->negate();

    return result;
  }

  void trim() { this->data->trim(); }
};
