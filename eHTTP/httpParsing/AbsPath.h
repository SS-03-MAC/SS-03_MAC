//===-- eHTTP/httpParsing/AbsPath.h -----------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of parsing for a AbsPath as defined
/// in RFC 2616.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <sstream>
#include <vector>

namespace httpParsing {
/// Parses an AbsPath to its components.
class AbsPath {
private:
  std::vector<std::string> elements;
  bool pathEndsInSlash = false;
  std::string queryString;

  // Finite state machine
  /// Start state
  int state0(int c);
  int state1(int c);
  int state2(int c);
  int state3(int c);
  int state4(int c);
  /// Error state. FSMError must be set.
  int state5();
  /// The string to throw in state 6 when there was a parsing error.
  std::string FSMError;
  /// A temporary string variable to accumulate data while parsing the input.
  std::stringstream FSMTemp;

public:
  /// Constructs an AbsPath from \p in.
  AbsPath(std::string &in);
  /// \returns the full path and query string (e.g. /api/users?id=1).
  std::string getPathAndQueryString();
  /// \returns the full path without the query string (e.g. /api/users)
  std::string getFullPath();
  /// \returns either the file name (or folder) if the path does not end in slash, otherwise NULL.
  std::string getFileName();
  /// \returns the query string (e.g. id=1).
  std::string getQueryString();
  /// Checks if the first element of the path is \p element.  Case insensitive.
  bool beginsWith(std::string element);
  /// \returns whether the path ends with a slash, usually indicating that the server must search the default documents.
  inline bool endsInSlash() { return pathEndsInSlash; }
  std::string getScriptPath();
};

std::ostream &operator<<(std::ostream &os, AbsPath &path);
}