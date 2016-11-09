#pragma once

#include "httpHeaderCollection.h"
#include "AbsPath.h"

class httpRequestHeaderCollection : public httpHeaderCollection {
private:
  std::string verb;

  std::string firstLineToString();
  void parseFirstLine();
public:
  httpRequestHeaderCollection(std::istream *input);
  httpRequestHeaderCollection(std::string verb, std::string path, std::string httpVersion);
  ~httpRequestHeaderCollection();

  httpParsing::AbsPath *path;
  std::string getVerb();
};