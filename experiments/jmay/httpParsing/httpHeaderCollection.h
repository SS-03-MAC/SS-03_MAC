#pragma once

#include <vector>
#include "httpHeader.h"

class httpHeaderCollection : public std::vector<httpHeader*> {
public:
  httpHeaderCollection(std::istream &input);

  std::string toString();
};