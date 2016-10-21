#include <sstream>
#include "httpRequestHeaderCollection.h"
#include "httpUtils.h"

httpRequestHeaderCollection::httpRequestHeaderCollection(std::istream *input) : httpHeaderCollection(input) {
  parseFirstLine();
}

httpRequestHeaderCollection::httpRequestHeaderCollection(std::string verb, std::string path, std::string httpVersion)
: httpHeaderCollection(httpVersion) {
  this->verb = verb;
  this->path = path;
}

std::string httpRequestHeaderCollection::firstLineToString() {
  std::stringstream out;
  out << verb << ' ' << path << ' ' << httpVersion;
  return out.str();
}

void httpRequestHeaderCollection::parseFirstLine() {
  std::stringstream headerStream(firstLine);

  // Parse fields
  verb = httpUtils::readToken(&headerStream);
  if (headerStream.eof()) {
    throw "Malformed request header";
  }
  path = httpUtils::readToken(&headerStream);
  if (headerStream.eof()) {
    throw "Malformed request header";
  }
  httpVersion = httpUtils::readToken(&headerStream);
  if (!headerStream.eof()) {
    throw "Request has garbage on the end of the line";
  }
}