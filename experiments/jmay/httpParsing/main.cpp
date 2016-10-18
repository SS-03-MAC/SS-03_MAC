#include <iostream>
#include "httpHeader.h"
int main() {
  httpHeader *h = new httpHeader("test: value");
  std::cout << h->key << std::endl;
  std::cout << h->value << std::endl;
  std::cout << *h << std::endl;
  delete h;
  return 0;
}