/*
 * Bignum library test cases
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include "bigint.h"

int main() {
  printf("a = 0xFFFFFFFFFFFFFFFF:\n");
  BigInt *a = new BigInt(0xFFFFFFFFFFFFFFFF);
  a->print();

  printf("b = 0x10:\n");
  BigInt *b = new BigInt(0x10);
  b->print();

  printf("c = b+a\n");
  // Appending:
  BigInt *c = b->add(a);
  c->print();

  printf("c = -c: \n");
  c->negate();
  c->print();

  printf("d = ba\n");
  BigInt *d = b->add(a);
  d->print();

  printf("j = d + c\n");
  BigInt *j = d->add(c);
  j->print();

  printf("e = -2\n");
  BigInt *e = new BigInt(0x02);
  e->negate();
  e->print();

  printf("f = 1\n");
  BigInt *f = new BigInt(0x01);
  f->print();

  printf("g = e + f\n");
  BigInt *g = e->add(f);
  g->print();

  printf("h = g + f\n");
  BigInt *h = g->add(f);
  h->print();

  printf("i = e - f\n");
  BigInt *i = e->subtract(f);
  i->print();

  delete a;
  delete b;
  delete c;
  delete d;
  delete e;
  delete f;
  delete g;
  delete h;
  delete i;
  delete j;
}
