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

  BigInt(bool negative, const uint8_t *val, uint64_t length) {
    uint64_t i = 0;
    this->negative = negative;
    this->data = new BigIntLL();
    for (i = 0; i < length; i++) {
      this->data->append(val[i]);
    }
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

  int cmp(const BigInt *val) {
    uint64_t t_l = this->data->non_zero_length();
    uint64_t v_l = val->data->non_zero_length();
    struct BigIntLLNode *t_c;
    struct BigIntLLNode *v_c;
    t_c = (struct BigIntLLNode *)(this->data->head)->next;
    v_c = (struct BigIntLLNode *)(val->data->head)->next;

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

  bool equals(const BigInt *val) { return (this->cmp(val) == 0); }

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
    uint8_t shift = (uint8_t)(amount % 8);
    struct BigIntLLNode *curr;
    struct BigIntLLNode *next;
    uint8_t next_mask = ((1 << shift) - 1);
    uint8_t data_mask = (0xFF << shift);

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

  void right_shift(uint64_t amount) {
    uint64_t times = 0;
    uint64_t bytes = amount / 8;
    uint64_t shift = amount % 8;

    struct BigIntLLNode *curr = (struct BigIntLLNode *)(this->data->tail->prev);
    struct BigIntLLNode *next = (struct BigIntLLNode *)(curr->prev);

    if (curr == this->data->head) {
      return;
    }

    uint8_t next_mask = (0xFF << amount);
    uint8_t data_mask = ((1 << amount) - 1);

    for (times = 0; times < bytes; times++) {
      this->data->remove_last();
    }

    this->data->rotr_each(shift);
    while (next != (struct BigIntLLNode *)data->head) {
      curr->data = (curr->data & data_mask) ^ (next->data & next_mask);

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

  BigInt *sub(const BigInt *v) {
    BigInt *result;
    BigInt *val = new BigInt(v);

    val->negate();
    result = this->add(val);
    val->negate();

    return result;
  }

  BigInt *mul(BigInt *v) {
    BigInt *result = new BigInt(uint64_t(0x00));
    BigInt *tmp = new BigInt(uint64_t(0x00));
    BigInt *mul = new BigInt(*this);
    BigInt *val = new BigInt(v);
    uint8_t i = 0;
    uint8_t lsb = 0;
    bool negative = (mul->negative != val->negative);
    mul->negative = false;
    val->negative = false;

    while (val->data->length != 0) {
      lsb = val->data->lsb();
      for (i = 0; i < 8; i++) {
        if ((lsb & 1) == 1) {
          delete result;
          result = tmp->add(mul);
          delete tmp;
          tmp = new BigInt(result);
        }
        lsb = lsb >> 1;
        mul->left_shift(1);
      }
      val->right_shift(8);
    }

    result->negative = negative;

    return result;
  }

  void trim() { this->data->trim(); }
};
