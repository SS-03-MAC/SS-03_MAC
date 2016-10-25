
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include "httpHeader.h"
#include "httpUtils.h"

httpHeader::httpHeader(std::istream *line) {
  std::stringstream tempString;
  int readVal;
  bool endOfSection = false;

  do {
    switch (readVal = line->get()) {
    case ':':endOfSection = true;
      break;
    case EOF:throw "Header is missing value";
    default:tempString << (char) readVal;
      break;
    }
  } while (!endOfSection);
// TODO remove trailing whitespace?
  key.resize(tempString.str().length());
  std::string tempStr = tempString.str();
  std::transform(tempStr.begin(), tempStr.end(), key.begin(), ::tolower);
  value = *new std::string();

  value = httpUtils::readUntilEndOfVal(line);
}

httpHeader::httpHeader(std::string key, std::string value) {
  this->key.resize(key.length());
  std::transform(key.begin(), key.end(), this->key.begin(), ::tolower);
  this->value.resize(value.length());
  std::transform(value.begin(), value.end(), this->value.begin(), ::tolower);
}

std::string httpHeader::toString() {
  std::stringstream out;
  out << key << ": ";
  // Replace LFs with (SP)CRLF
  for (int i = 0; i < value.length(); i++) {
    if (value[i] == '\n') {
      out << "\r\n ";
    } else {
      out << value[i];
    }
  }
  return out.str();
}

std::ostream &operator << (std::ostream &os, httpHeader &header){
  os << header.toString();
  return os;
}