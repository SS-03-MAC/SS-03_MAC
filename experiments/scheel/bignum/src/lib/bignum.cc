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
  for (i = 0; i < length; i++) {
    this->data->append(val[i]);
  }
}

BigInt::BigInt(const BigInt *val) {
  this->negative = val->negative;
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

int BigInt::cmp(const BigInt *val) {
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

  while (t_c != this->data->tail && t_c->data == 0x00) {
    t_c = (struct BigIntLLNode *)t_c->next;
  }

  while (v_c != this->data->tail && v_c->data == 0x00) {
    v_c = (struct BigIntLLNode *)v_c->next;
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
