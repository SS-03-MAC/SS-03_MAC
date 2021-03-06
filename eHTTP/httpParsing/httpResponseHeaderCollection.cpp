//===-- eHTTP/httpParsing/httpResponseHeaderCollection.cpp ------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a implementation of the httpHeaderCollection for a HTTP
/// response.
///
//===----------------------------------------------------------------------===//

#include <sstream>

#include "httpResponseHeaderCollection.h"

httpResponseHeaderCollection::httpResponseHeaderCollection(std::istream *input) : httpHeaderCollection(input) {
  parseFirstLine();
}

httpResponseHeaderCollection::httpResponseHeaderCollection(std::string httpVersion,
                                                           int statusVal,
                                                           std::string statusDescription)
    : httpHeaderCollection(httpVersion) {
  this->statusVal = statusVal;
  this->statusDescription = statusDescription;
}

void httpResponseHeaderCollection::parseFirstLine() {
  unsigned long versionEnd;
  unsigned long statusValEnd;

  // Find separations
  versionEnd = firstLine.find(' ', 0);
  statusValEnd = firstLine.find(' ', versionEnd + 1);
  // Parse HTTP version
  httpVersion = firstLine.substr(0, versionEnd);
  // Parse status val
  statusVal = std::stoi(firstLine.substr(versionEnd + 1, statusValEnd - versionEnd - 1));
  // Parse status string
  statusDescription = firstLine.substr(statusValEnd + 1, std::string::npos);
}

std::string httpResponseHeaderCollection::firstLineToString() {
  std::stringstream out;
  out << httpVersion << " " << statusVal << " " << statusDescription;
  return out.str();
}