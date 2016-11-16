//===-- eHTTP/httpParsing/httpHeaderCollection.h ----------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains an implementation of a HTTP header collection.  It's
/// designed to be extended with request and response implementations to handle
/// the first line.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>

#include "httpHeader.h"

/// Represents an abstract collection of HTTP headers.  Since requests and responses have different status lines, this
/// class must be extended.
class httpHeaderCollection : public std::vector<httpHeader *> {
private:
  /// Trims a \\r from \p toTrim to deal with artifacts of \\r\\n line endings.
  static int trimTrailingCR(std::string &toTrim);
  /// Abstract method that creates a string of the request or response data for the first line of toString().
  virtual std::string firstLineToString() = 0;
protected:
  /// The HTTP version (e.g. HTTP/1.1)
  std::string httpVersion;
  // This is because the parent constructor must read headers after the first line, which the subclass must use.
  /// This is where the constructor stores the first line of the input for later parsing by subclasses.
  std::string firstLine;

  /// Reads a line from \p input, trims the \\r (if present) and stores the value in \p out.
  static void getLineAndTrim(std::istream &input, std::string &out);
public:
  /// Stores the first line in firstLine for parsing by subclasses, then parses the headers until \\r\\n\\r\\n.
  httpHeaderCollection(std::istream *input);
  /// Creates an empty header collection with the specified httpVersion.
  httpHeaderCollection(std::string httpVersion);

  std::string toString();
  int getIntVal(std::string key);
  /// Finds the \p key, then converts the value to an int64.
  int64_t getInt64Value(std::string key);
  /// \returns whether \p key exists in the collection (may have an empty value).
  bool keyExists(std::string key);
};

std::ostream &operator<<(std::ostream &os, httpHeaderCollection &headerCollection);
