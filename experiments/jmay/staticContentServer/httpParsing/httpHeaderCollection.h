#pragma once

#include <vector>
#include "httpHeader.h"

class httpHeaderCollection : public std::vector<httpHeader *> {
private:
  static int trimTrailingCR(std::string &toTrim);
  virtual std::string firstLineToString() = 0;
protected:
  std::string httpVersion;
  // This is because the parent constructor must read headers after the first line, which the subclass must use.
  std::string firstLine;

  static void getLineAndTrim(std::istream &input, std::string &out);
public:
  httpHeaderCollection(std::istream *input);
  httpHeaderCollection(std::string httpVersion);

  std::string toString();
};

std::ostream &operator<<(std::ostream &os, httpHeaderCollection &headerCollection);
