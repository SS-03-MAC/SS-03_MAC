/*
 * Bignum library -- linked list implementation
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

struct BigIntLLNode {
  void *prev;
  void *next;

  uint8_t data;
};

class BigIntLL {
public:
  size_t length;
  struct BigIntLLNode *head;
  struct BigIntLLNode *tail;

  BigIntLL() {
    this->length = 0;

    // Setup dummy head
    head = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;

    // Setup dummy tail
    tail = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = (void *)head;
    tail->next = NULL;
    head->next = (void *)tail;
  };

  BigIntLL(uint64_t val) {
    size_t i = 0;
    struct BigIntLLNode *curr;
    struct BigIntLLNode *new_node;
    this->length = 8;

    // Setup dummy head
    head = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;
    head->next = NULL;

    // Setup dummy tail
    tail = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = NULL;
    tail->next = NULL;

    curr = head;

    for (i = 8; i > 0; i--) {
      new_node = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
      curr->next = (void *)new_node;
      ((struct BigIntLLNode *)curr->next)->prev = (void *)curr;
      ((struct BigIntLLNode *)curr->next)->next = (void *)tail;
      ((struct BigIntLLNode *)curr->next)->data = (uint8_t)(val >> (i - 1) * 8);
      tail->prev = curr->next;

      curr = (struct BigIntLLNode *)curr->next;
    }

    trim();
  };

  BigIntLL(const BigIntLL *val) {
    size_t i = 0;
    struct BigIntLLNode *curr;
    struct BigIntLLNode *new_node;
    struct BigIntLLNode *val_curr;

    this->length = val->length;

    // Setup dummy head
    head = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    head->data = 0xFF;
    head->prev = NULL;
    head->next = NULL;

    // Setup dummy tail
    tail = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
    tail->data = 0xFF;
    tail->prev = NULL;
    tail->next = NULL;

    curr = head;
    val_curr = (struct BigIntLLNode *)(val->head->next);

    for (i = 0; i < val->length; i++) {
      new_node = (struct BigIntLLNode *)malloc(sizeof(BigIntLLNode) * 1);
      curr->next = (void *)new_node;
      ((struct BigIntLLNode *)curr->next)->prev = (void *)curr;
      ((struct BigIntLLNode *)curr->next)->next = (void *)tail;
      ((struct BigIntLLNode *)curr->next)->data = val_curr->data;
      tail->prev = curr->next;

      curr = (struct BigIntLLNode *)curr->next;
      val_curr = (struct BigIntLLNode *)val_curr->next;
    }

    trim();
  };

  ~BigIntLL() {
    struct BigIntLLNode *curr;
    struct BigIntLLNode *next;
    curr = head;

    while (curr != tail) {
      next = (struct BigIntLLNode *)curr->next;
      free(curr);
      curr = next;
    }
    free(tail);
  }

  void print() {
    struct BigIntLLNode *curr;
    curr = (struct BigIntLLNode *)(this->head)->next;

    printf("0x");

    if (curr == tail) {
      printf("00");
      return;
    }

    while (curr != tail) {
      printf("%02x", curr->data);

      curr = (struct BigIntLLNode *)curr->next;
    }
  };

  void rev_print() {
    struct BigIntLLNode *curr;
    curr = (struct BigIntLLNode *)(this->tail)->prev;

    if (curr == head) {
      printf("00");
      return;
    }

    while (curr != head) {
      printf("%02x", curr->data);

      curr = (struct BigIntLLNode *)curr->prev;
    }
  };

  void trim() {
    struct BigIntLLNode *curr;
    curr = (struct BigIntLLNode *)(this->head)->next;

    if (this->length == 0) {
      return;
    }

    while (curr->data == 0) {
      curr = (struct BigIntLLNode *)(curr->next);
      remove_first();
    }
  }

  void remove_first() {
    if (this->length != 0) {
      this->length -= 1;

      struct BigIntLLNode *del = (struct BigIntLLNode *)(this->head->next);
      struct BigIntLLNode *next = (struct BigIntLLNode *)(del->next);
      head->next = next;
      next->prev = head;
      free(del);
    }
  }

  void remove_last() {
    if (this->length != 0) {
      this->length -= 1;

      struct BigIntLLNode *del = (struct BigIntLLNode *)(this->tail)->prev;
      struct BigIntLLNode *prev = (struct BigIntLLNode *)(del->prev);
      tail->prev = prev;
      prev->next = tail;
      free(del);
    }
  }

  void prepend(const uint8_t val) {
    struct BigIntLLNode *curr;

    curr = (struct BigIntLLNode *)malloc(sizeof(struct BigIntLLNode) * 1);
    curr->data = val;

    curr->prev = (void *)head;
    curr->next = head->next;
    ((struct BigIntLLNode *)head->next)->prev = (void *)curr;
    head->next = (void *)curr;

    this->length += 1;
  };

  void append(const uint8_t val) {
    struct BigIntLLNode *curr;

    curr = (struct BigIntLLNode *)malloc(sizeof(struct BigIntLLNode) * 1);
    curr->data = val;

    curr->next = (void *)tail;
    curr->prev = tail->prev;
    ((struct BigIntLLNode *)tail->prev)->next = (void *)curr;
    tail->prev = (void *)curr;

    this->length += 1;
  };

  uint8_t msb() {
    if (head->next != tail) {
      return ((struct BigIntLLNode *)head->next)->data;
    } else {
      return 0;
    }
  }

  uint8_t lsb() {
    if (head->next != tail) {
      return ((struct BigIntLLNode *)tail->prev)->data;
    } else {
      return 0;
    }
  }

  void rotl_one(struct BigIntLLNode *pos, uint8_t amount) {
    pos->data = (pos->data << amount) | (pos->data >> (8 - amount));
  }

  void rotl_each(uint8_t amount) {
    struct BigIntLLNode *curr;
    curr = (struct BigIntLLNode *)(this->head)->next;

    while (curr != tail) {
      if (curr->data != 0x00) {
        rotl_one(curr, amount);
      }

      curr = (struct BigIntLLNode *)curr->next;
    }
  }

  void rotr_one(struct BigIntLLNode *pos, uint8_t amount) {
    pos->data = (pos->data << (8 - amount)) | (pos->data >> amount);
  }

  void rotr_each(uint8_t amount) {
    struct BigIntLLNode *curr;
    curr = (struct BigIntLLNode *)(this->head)->next;

    // Ingore leading zeros
    while (curr != tail) {
      if (curr->data != 0x00) {
        break;
      }

      curr = (struct BigIntLLNode *)curr->next;
    }

    while (curr != tail) {
      rotr_one(curr, amount);

      curr = (struct BigIntLLNode *)curr->next;
    }
  }
};
