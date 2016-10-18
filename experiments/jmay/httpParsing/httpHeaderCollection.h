#pragma once

#include <vector>
#include "httpHeader.h"

class httpHeaderCollection : public std::vector<httpHeader *> {
private:
  std::string httpVersion;
  int statusVal;
  std::string statusDescription;

  static int trimTrailingCR(std::string &toTrim);
  static void getlineAndTrim(std::istream &input, std::string &out);
  void parseHeaders(std::string &headerLine);

public:
  httpHeaderCollection(std::istream &input);

  std::string toString();
};