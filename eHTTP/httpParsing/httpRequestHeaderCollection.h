//===-- eHTTP/httpParsing/httpRequestHeaderCollection.h ---------*- C++ -*-===//
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

#pragma once

#include "httpHeaderCollection.h"
#include "AbsPath.h"

/// Represents a HTTP request with its headers.
class httpRequestHeaderCollection : public httpHeaderCollection {
private:
  /// HTTP verb of this request
  std::string verb;

  std::string firstLineToString();
  void parseFirstLine();
public:
  httpRequestHeaderCollection(std::istream *input);
  httpRequestHeaderCollection(std::string verb, std::string path, std::string httpVersion);
  ~httpRequestHeaderCollection();
  inline std::string getVerb() { return verb; }

  /// The path of this HTTP request.
  httpParsing::AbsPath *path;
};