#pragma once

#include <string>
#include <vector>

namespace httpParsing {
class AbsPath {
private:
  std::vector<std::string> elements;
  bool pathEndsInSlash = false;
  std::string queryString;
  enum elementType {
    end,
    slashEnd,
    slashQueryString,
    path,
    queryString
  };

  std::string getElement(std::string &in, int start);
  elementType nextElementType(std::string &in, int start);

public:
  AbsPath(std::string &in);
};
}