#include <iostream>
#include <sstream>
#include "httpHeader.h"
#include "httpHeaderCollection.h"
#include "httpResponseHeaderCollection.h"
#include "httpRequestHeaderCollection.h"
#include "AbsPath.h"

int main() {
  httpParsing::AbsPath *p;
  std::string test = "/t/test%20/t.php?hi=hel%20lo&test2&yes";
  try {
    p = new httpParsing::AbsPath(test);
  } catch (std::string err) {
    std::cout << err << std::endl;
    return 1;
  }
  std::cout << p->getFullPath() << std::endl;
  std::cout << p->getFileName() << std::endl;
  std::cout << p->getQueryString() << std::endl;
  return 0;
}