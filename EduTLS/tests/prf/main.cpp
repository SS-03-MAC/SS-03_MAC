/*
 * MD5 test cases
 *
 * Copyright (C) 2016 Alexander Scheel
*/

#include "tests.h"
#include <cstdio>

int main() {
  int (*func)();
  int results = 0;
  int current = 0;

  void *element = tests_f[current];

  while (element != NULL) {
    printf("[%i] %s", current, tests_n[current].c_str());
    func = (int (*)())element;
    results = func();
    if (results != 0) {
      return results;
    }
    printf(" ok\n");
    current += 1;
    element = tests_f[current];
  }

  return 0;
}
