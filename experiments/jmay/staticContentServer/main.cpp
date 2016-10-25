#include <iostream>
#include "httpParsing/httpHeader.h"

int main() {
  httpHeader *h = new httpHeader("test", "test");
  std::cout << *h << std::endl;
  return 0;
}