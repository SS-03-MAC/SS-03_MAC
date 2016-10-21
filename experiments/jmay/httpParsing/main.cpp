#include <iostream>
#include <sstream>
#include "httpHeader.h"
#include "httpHeaderCollection.h"
#include "httpResponseHeaderCollection.h"
#include "httpRequestHeaderCollection.h"

int main() {
  std::string *s1 = new std::string("HTTP/1.1 400 Bad Request\r\ntest: value\r\n more value\r\nanother: test2\r\n\r\n");
  std::string *s2 = new std::string("again");
  std::istringstream ss(*s1);
  httpResponseHeaderCollection *hc = new httpResponseHeaderCollection(&ss);
  std::cout << *hc << std::endl;

  httpResponseHeaderCollection collection("HTTP/1.1", 404, "Not Found");
  std::string key = "test";
  std::string value = "test value #1";
  httpHeader header1(key, value);
  key = "New Test";
  value = "value for new test";
  httpHeader header2(key, value);
  collection.push_back(&header1);
  collection.push_back(&header2);
  std::cout << collection << std::endl;

  std::cout << "Request" << std::endl;
  std::string *s3 = new std::string("GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n");
  std::istringstream ssRequest(*s3);
  httpRequestHeaderCollection requestCollection(&ssRequest);
  std::cout << requestCollection << std::endl;
  std::cout << "Fin" << std::endl;
  return 0;
}