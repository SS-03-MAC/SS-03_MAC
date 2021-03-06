//===-- eHTTP/httpParsing/AbsPath.cpp ---------------------------*- C++ -*-===//
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

#include <sstream>
#include <iostream>
#include "AbsPath.h"
#include "httpUtils.h"

using httpParsing::AbsPath;

AbsPath::AbsPath(std::string &in) {
  int state = 0;
  int currentChar;
  std::stringstream currentElement(in);
  do {
    // Read char
    currentChar = currentElement.get();

    // Parse char
    // State 6 is the final state
    // State 5 is the error state
    switch (state) {
    case 0:state = state0(currentChar);
      break;
    case 1:state = state1(currentChar);
      break;
    case 2:state = state2(currentChar);
      break;
    case 3:state = state3(currentChar);
      break;
    case 4:state = state4(currentChar);
      break;
    case 5:state = state5();
      break;
    default:throw "Finite state machine is broken";
    }
  } while (state != 6);
  queryString = httpUtils::uriDecode(queryString);
}

int AbsPath::state0(int c) {
  std::cout << "state0" << std::endl;
  // Path must start with '/'
  if (c == '/') {
    return 1;
  }
  FSMError = "Path must start with '/'";
  return 5;
}

int AbsPath::state1(int c) {
  std::cout << "state1" << std::endl;
  // Parse the path & file name
  if (c == EOF || c == '/' || c == '?') {
    // Transition out of this token
    if (FSMTemp.str() == "..") {
      if (elements.size() > 0) {
        elements.pop_back();
      } else {
        // .. in path trying to escape from web server
        FSMError = "Path escapes web root";
        return 5;
      }
    } else if (FSMTemp.str() != ".") {
      std::string tempStr = FSMTemp.str();
      elements.push_back(httpUtils::uriDecode(tempStr));
    }
    FSMTemp.str("");
    if (c == EOF) {
      return 6;
    } else if (c == '/') {
      return 2;
    } else { // c == '?'
      return 3;
    }
  } else if (httpUtils::isUriPchar((char) c)) {
    FSMTemp << (char) c;
    return 1;
  }
  FSMError = "Unexpected character in path";
  return 5;
}

int AbsPath::state2(int c) {
  std::cout << "state2" << std::endl;
  // Parse path separator ('/')
  if (c == EOF) {
    pathEndsInSlash = true;
    return 6;
  } else if (c == '/') {
    return 2;
  } else if (c == '?') {
    pathEndsInSlash = true;
    return 3;
  } else if (httpUtils::isUriPchar((char) c)) {
    FSMTemp << (char) c;
    return 1;
  }
  FSMError = "Unexpected character in path";
  return 5;
}

int AbsPath::state3(int c) {
  std::cout << "state3" << std::endl;
  // Parse the querystring key
  if (c == EOF) {
    return 6;
  } else if (c == '&') {
    // Begin another key (this key has no value)
    queryString += '&';
    return 3;
  } else if (c == '=') {
    // Begin the value
    queryString += '=';
    return 4;
  } else if (httpUtils::isQueryStringSafe((char) c)) {
    queryString += (char) c;
    return 3;
  }
  FSMError = "Invalid character in querystring";
  return 5;
}

int AbsPath::state4(int c) {
  std::cout << "state4" << std::endl;
  // Parse the querystring value
  if (c == EOF) {
    return 6;
  } else if (c == '&') {
    // Begin new value
    queryString += '&';
    return 3;
  } else if (httpUtils::isQueryStringSafe((char) c)) {
    queryString += (char) c;
    return 4;
  }
  FSMError = "Invalid character in querystring value";
  return 5;
}

int AbsPath::state5() {
  std::cout << "state5" << std::endl;
  // Error state
  throw FSMError;
}

std::string AbsPath::getPathAndQueryString() {
  if (queryString.length() == 0) {
    return getFullPath();
  } else {
    return getFullPath() + "?" + getQueryString();
  }
}

std::string AbsPath::getFullPath() {
  std::stringstream out;
  for (unsigned int i = 0; i < elements.size(); i++) {
    out << '/' << elements[i];
  }
  if (pathEndsInSlash) {
    out << "/";
  }
  return out.str();
}

std::string AbsPath::getFileName() {
  if (pathEndsInSlash) {
    // Path ends in '/', so there is no file name
    return NULL;
  }
  return elements.back();
}

std::string AbsPath::getQueryString() {
  return queryString;
}

bool AbsPath::beginsWith(std::string element) {
  //TODO The path should be parsed now to prevent escaping "/"
  if (elements.size() == 0) {
    return element == "";
  }
  return element == elements[0];
}

std::ostream &operator<<(std::ostream &os, AbsPath &path) {
  return os << path.getPathAndQueryString();
}

std::string AbsPath::getScriptPath() {
  std::stringstream out;
  for (unsigned int i = 1; i < elements.size(); i++) {
    out << "/" << elements[i];
  }
  if (pathEndsInSlash) {
    out << "/";
  }
  return out.str();
}
