#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace httpParsing {
class AbsPath {
private:
  std::vector<std::string> elements;
  bool pathEndsInSlash = false;
  std::string queryString;

  // Finite state machine
  int state0(int c);
  int state1(int c);
  int state2(int c);
  int state3(int c);
  int state4(int c);
  int state5();
  std::string FSMError;
  std::stringstream FSMTemp;

public:
  AbsPath(std::string &in);
  std::string getFullPath();
  std::string getFileName();
  std::string getQueryString();
  bool beginsWith(std::string element);
};
}