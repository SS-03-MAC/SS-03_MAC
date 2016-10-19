#include <iostream>
#include "httpHeader.h"
#include "httpHeaderCollection.h"

int main() {
  /*httpHeader *h = new httpHeader("test: value");
  httpHeader *h2 = new httpHeader("Another: test");
  std::cout << h->key << std::endl;
  std::cout << h->value << std::endl;
  std::cout << *h << std::endl;

  std::string *s1 = new std::string("HTTP/1.1 400 Bad Request\r\ntest: value\r\nanother: test2\r\n\r\n");
  std::string *s2 = new std::string("again");
  std::istringstream ss(*s1);
  httpHeaderCollection *hc = new httpHeaderCollection(ss);
  hc->push_back(h);
  hc->push_back(h2);
  std::cout << hc->size() << std::endl;
  std::cout << hc->toString();
  std::cout << "Fin" << std::endl;
  delete h;*/

  httpHeaderCollection collection("HTTP/1.1", 404, "Not Found");
  std::string key = "test";
  std::string value = "test value #1";
  httpHeader header1(key, value);
  key = "New Test";
  value = "value for new test";
  httpHeader header2(key, value);
  collection.push_back(&header1);
  collection.push_back(&header2);
  std::cout << collection.toString() << std::endl;
  return 0;
}