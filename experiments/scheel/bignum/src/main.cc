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

  printf("j trim();\n");
  j->trim();
  j->print();

  printf("j trim();\n");
  j->trim();
  j->print();

  printf("e = -2\n");
  BigInt *e = new BigInt(0x02);
  e->negate();
  e->print();

  printf("e trim();\n");
  e->trim();
  e->print();

  printf("e trim();\n");
  e->trim();
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
  BigInt *i = e->sub(f);
  i->print();

  printf("k = 1 << 1\n");
  BigInt *k = new BigInt(0x01);
  k->left_shift(1);
  k->print();
  printf("k = 2 << 4\n");
  k->left_shift(0x04);
  k->print();
  printf("k = 32 >> 4\n");
  k->right_shift(0x04);
  k->print();
  printf("k = 2 >> 1\n");
  k->right_shift(0x01);
  k->print();
  printf("k = 1 << 20\n");
  k->left_shift(20);
  k->print();

  printf("l = 2\n");
  BigInt *l = new BigInt(0x02);
  printf("m = 3\n");
  BigInt *m = new BigInt(0x03);
  printf("n = m*l\n");
  BigInt *n = m->mul(l);
  n->print();
  printf("o = n*n\n");
  BigInt *o = n->mul(n);
  o->print();
  printf("p = o*e\n");
  BigInt *p = o->mul(e);
  p->print();

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
  delete k;
  delete l;
  delete m;
  delete n;
  delete o;
}
