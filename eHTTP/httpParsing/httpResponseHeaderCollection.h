//===-- eHTTP/httpParsing/httpResponseHeaderCollection.h --------*- C++ -*-===//
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

#pragma once

#include "httpHeaderCollection.h"

/// Represents a HTTP response with its headers.
class httpResponseHeaderCollection : public httpHeaderCollection {
private:
  /// The numeric status of the response
  int statusVal;
  /// The text description of this response
  std::string statusDescription;

  std::string firstLineToString();
  void parseFirstLine();
public:
  httpResponseHeaderCollection(std::istream *input);
  httpResponseHeaderCollection(std::string httpVersion, int statusVal, std::string statusDescription);
};