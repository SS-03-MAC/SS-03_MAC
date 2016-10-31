#include <sstream>
#include "AbsPath.h"
#include "httpUtils.h"

using httpParsing::AbsPath;

std::string AbsPath::getElement(std::string &in, int start) {
  std::stringstream out;
  std::string temp;
  char c;
  while (in[start] == '/') {
    start++;
  }
  do {
    out << in[start];
    start++;
  } while (start < in.length() && in[start] != '/');
  temp = out.str();
  return httpUtils::uriDecode(temp);
}

AbsPath::elementType AbsPath::nextElementType(std::string &in, int start) {
  if (start >= in.length()) {
    return end;
  }
  if (in[start] == '?') {
    return queryString;
  } else if (in[start] != '/') {
    throw "Expected / or ? in the path.";
  }
  for (int i = start + 1; i < in.length(); i++) {
    if (in[i] == '?') {
      return slashQueryString;
    } else if (in[i] != '/') {
      return path;
    }
  }
  return slashEnd;
}

AbsPath::AbsPath(std::string &in) {
  std::stringstream currentElement;
  bool firstElement = true;
  if (in.length() == 0 || in[0] != '/') {
    throw "AbsPath must start with /.";
  }

}