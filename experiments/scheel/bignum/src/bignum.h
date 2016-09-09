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

    head->next = malloc(sizeof(BigIntLLNode) * 1);
    ((struct BigIntLLNode*) head->next)->prev = (void *)head;
    ((struct BigIntLLNode*) head->next)->next = (void *)tail;
    ((struct BigIntLLNode*) head->next)->data = 0;
  };

  BigIntLL(uint64_t val) {
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

    size_t i = 0;
    struct BigIntLLNode* curr;

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

    curr = head;
    val_curr = (struct BigIntLLNode*) (val.head->next);

    for (i = 0; i < val.length; i++) {
      curr->next = malloc(sizeof(BigIntLLNode) * 1);
      ((struct BigIntLLNode*) curr->next)->prev = (void *)curr;
      ((struct BigIntLLNode*) curr->next)->next = (void *)tail;
      ((struct BigIntLLNode*) curr->next)->data = 0;

      curr =     (struct BigIntLLNode*) curr->next;
      val_curr = (struct BigIntLLNode*) val_curr->next;
    }
  };

  void print() {
    size_t i = 0;
    struct BigIntLLNode* curr;
    curr = (struct BigIntLLNode*) this->head->next;

    for (i = 0; i < this->length; i++) {
      printf("%02x", curr->data);

      curr = (struct BigIntLLNode*) curr->next;
    }
  };
};

class BigInt {
private:
  bool sign;
  BigIntLL data;

public:
  BigInt() {
    data = BigIntLL();
  };

  BigInt(uint64_t val) {
    data = BigIntLL(val);
  };

  void print() {
    data.print();
  }
};
