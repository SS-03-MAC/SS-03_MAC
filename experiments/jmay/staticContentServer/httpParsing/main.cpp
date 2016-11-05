#include <iostream>
#include <sstream>
#include "httpHeader.h"
#include "httpHeaderCollection.h"
#include "httpResponseHeaderCollection.h"
#include "httpRequestHeaderCollection.h"
#include "AbsPath.h"

int main() {
  httpParsing::AbsPath *p;
  std::string test = "/t/t.php?hi=hello";
  try {
    p = new httpParsing::AbsPath(test);
  } catch (const char *err) {
    std::cout << err << std::endl;
  }
  return 0;
}