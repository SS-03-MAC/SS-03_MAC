#pragma once

#include "httpHeaderCollection.h"

class httpResponseHeaderCollection : public httpHeaderCollection {
private:
  int statusVal;
  std::string statusDescription;

  std::string firstLineToString();
  void parseFirstLine();
public:
  httpResponseHeaderCollection(std::istream *input);
  httpResponseHeaderCollection(std::string httpVersion, int statusVal, std::string statusDescription);
};