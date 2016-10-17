#pragma once

#include <string>
#include <sstream>
class httpHeader {
public:
  std::string key;
  std::string value;

  httpHeader(std::string line);

  ~httpHeader() {
    delete &key;
    delete &value;
  }
};