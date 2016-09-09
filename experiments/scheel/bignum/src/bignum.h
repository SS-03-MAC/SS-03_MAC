/*
 * Bignum library
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

struct BigIntLLNode {
  void *prev;
  void *next;

  uint8_t data;
};

class BigIntLL {
private:
  size_t length;
  struct BigIntLLNode *head;
  struct BigIntLLNode *tail;

public:
  BigIntLL() {
    struct BigIntLLNode* curr;
    this->length = 1;

    // Setup dummy head
    head = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;
    head->next = NULL;

    // Setup dummy tail
    tail = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = NULL;
    tail->next = NULL;

    curr = (BigIntLLNode*) head->next;

    curr = (struct BigIntLLNode*) malloc(sizeof(struct BigIntLLNode) * 1);
    curr->prev = (void *)head;
    curr->next = (void *)tail;
    curr->data = 0;
  };

  BigIntLL(uint64_t val) {
    size_t i = 0;
    struct BigIntLLNode* curr;
    this->length = 8;

    // Setup dummy head
    head = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;
    head->next = NULL;

    // Setup dummy tail
    tail = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = NULL;
    tail->next = NULL;

    curr = head;

    for (i = 8; i > 0; i--) {
      curr->next = malloc(sizeof(BigIntLLNode) * 1);
      ((struct BigIntLLNode*) curr->next)->prev = (void *)curr;
      ((struct BigIntLLNode*) curr->next)->next = (void *)tail;
      ((struct BigIntLLNode*) curr->next)->data = (uint8_t) (val >> (i-1)*8);

      curr = (struct BigIntLLNode*) curr->next;
    }
  };

  BigIntLL(const BigIntLL& val) {
    size_t i = 0;
    struct BigIntLLNode* curr;
    struct BigIntLLNode* val_curr;

    this->length = val.length;

    // Setup dummy head
    head = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;
    head->next = NULL;

    // Setup dummy tail
    tail = (BigIntLLNode*) malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = NULL;
    tail->next = NULL;

    curr = head;
    val_curr = (struct BigIntLLNode*) (val.head->next);

    for (i = 0; i < val.length; i++) {
      curr->next = malloc(sizeof(BigIntLLNode) * 1);
      ((struct BigIntLLNode*) curr->next)->prev = (void *)curr;
      ((struct BigIntLLNode*) curr->next)->next = (void *)tail;
      ((struct BigIntLLNode*) curr->next)->data = val_curr->data;

      curr =     (struct BigIntLLNode*) curr->next;
      val_curr = (struct BigIntLLNode*) val_curr->next;
    }
  };

  void print() {
    size_t i = 0;
    struct BigIntLLNode* curr;
    curr = (struct BigIntLLNode*) (this->head)->next;

    // Ingore leading zeros
    while (curr != tail) {
      if (curr->data != 0x00) {
        break;
      }

      curr = (struct BigIntLLNode*) curr->next;
    }

    while (curr != tail) {
      printf("%02x", curr->data);

      curr = (struct BigIntLLNode*) curr->next;
    }

    printf("\n");
  };
};

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

  BigInt(const BigInt& val) {
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
  }

  void add(const BigInt& val) {

  }

  void shift(uint64_t bits) {

  }
};
