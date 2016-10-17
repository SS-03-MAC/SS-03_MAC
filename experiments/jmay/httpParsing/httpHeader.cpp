
#include "httpHeader.h"

httpHeader::httpHeader(std::string line) {
  std::stringstream tempString;
  int i = 0;
  bool endOfSection = false;

  do {
    switch (line[i]) {
    case ':':endOfSection = true;
      break;
    case '\0':throw "Header is missing value";
    default:tempString << line[i];
      break;
    }
    i++;
  } while (!endOfSection);
// TODO remove trailing whitespace?
  key = tempString.str();
  value = *new std::string();

  // Skip whitespace
  endOfSection = false;
  do {
    switch (line[i]) {
    case ' '://TODO is anything else whitespace
      i++;
      break;
    case '\0':
      throw "Value is missing";
    default:
      endOfSection = true;
    }
  } while (!endOfSection);

  tempString.str(std::string());
  do {
    // TODO can value be empty?
    tempString << line[i++];
  } while (line[i] != '\0');
  value = tempString.str();
}