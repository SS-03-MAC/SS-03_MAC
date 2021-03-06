//===-- eHTTP/httpParsing/httpRequestHeaderCollection.cpp -------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a implementation of the httpHeaderCollection for a HTTP
/// request.
///
//===----------------------------------------------------------------------===//

#include <sstream>

#include "httpRequestHeaderCollection.h"
#include "httpUtils.h"

httpRequestHeaderCollection::httpRequestHeaderCollection(std::istream *input) : httpHeaderCollection(input) {
  parseFirstLine();
}

httpRequestHeaderCollection::httpRequestHeaderCollection(std::string verb, std::string path, std::string httpVersion)
    : httpHeaderCollection(httpVersion) {
  this->verb = verb;
  this->path = new httpParsing::AbsPath(path);
}

std::string httpRequestHeaderCollection::firstLineToString() {
  std::stringstream out;
  out << verb << ' ' << path->getPathAndQueryString() << ' ' << httpVersion;
  return out.str();
}

void httpRequestHeaderCollection::parseFirstLine() {
  std::stringstream headerStream(firstLine);
  std::string pathString;

  // Parse fields
  verb = httpUtils::readToken(&headerStream);
  if (headerStream.eof()) {
    throw "Malformed request header";
  }
  pathString = httpUtils::readToken(&headerStream);
  path = new httpParsing::AbsPath(pathString);
  if (headerStream.eof()) {
    throw "Malformed request header";
  }
  httpVersion = httpUtils::readToken(&headerStream);
  if (!headerStream.eof()) {
    throw "Request has garbage on the end of the line";
  }
}

httpRequestHeaderCollection::~httpRequestHeaderCollection() {
  delete path;
}
