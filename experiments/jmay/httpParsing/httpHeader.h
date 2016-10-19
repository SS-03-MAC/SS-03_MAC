#pragma once

#include <string>
#include <sstream>
class httpHeader {
public:
  std::string key;
  std::string value;

  httpHeader(std::string line);
  httpHeader(std::string key, std::string value);
  ~httpHeader() {
    delete &key;
    delete &value;
  }

  std::string toString();
};

std::ostream &operator<<(std::ostream &os, httpHeader &header);