//===-- eHTTP/httpParsing/httpHeader.h --------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a representation of a HTTP header.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <istream>

/// Represents a single HTTP header of a key and value.
class httpHeader {
public:
  /// The unescaped key of the header.
  std::string key;
  /// The unescaped value of the header.
  std::string value;

  /// Parses a header from an istream.
  httpHeader(std::istream *line);
  /// Created a header from the unescaped \p key and \p value.
  httpHeader(std::string key, std::string value);
  ~httpHeader() {
    delete &key;
    delete &value;
  }

  std::string toString();
};

std::ostream &operator<<(std::ostream &os, httpHeader &header);