#include <iostream>
#include <sstream>
#include "httpHeader.h"
#include "httpHeaderCollection.h"

int main() {
  std::string *s1 = new std::string("HTTP/1.1 400 Bad Request\r\ntest: value\r\n more value\r\nanother: test2\r\n\r\n");
  std::string *s2 = new std::string("again");
  std::istringstream ss(*s1);
  httpHeaderCollection *hc = new httpHeaderCollection(&ss);
  std::cout << *hc << std::endl;

  httpHeaderCollection collection("HTTP/1.1", 404, "Not Found");
  std::string key = "test";
  std::string value = "test value #1";
  httpHeader header1(key, value);
  key = "New Test";
  value = "value for new test";
  httpHeader header2(key, value);
  collection.push_back(&header1);
  collection.push_back(&header2);
  std::cout << collection << std::endl;
  std::cout << "Fin" << std::endl;
  return 0;
}