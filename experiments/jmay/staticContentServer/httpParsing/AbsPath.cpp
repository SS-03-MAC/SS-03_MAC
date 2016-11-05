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
    // State 2 is the final state
    // State 5 is the error state
    switch (state) {
    case 0:
      state = state0(currentChar);
      break;
    case 1:
      state = state1(currentChar);
      break;
    case 2:
      state = state2(currentChar);
      break;
    case 3:
      state = state3(currentChar);
      break;
    case 4:
      state = state4(currentChar);
      break;
    case 5:
      state = state5(currentChar);
      break;
    default:
      throw "Finite state machine is broken";
    }
  } while (state != 2);
  // todo?
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
  if (c == EOF) {
    return 2;
  } else if (c == '/') {
    return 1;
  } else if (c == '?') {
    return 3;
  } else if (httpUtils::isUrlSafe((char) c)) {
    return 1;
  }
  FSMError = "Unexpected character in path";
  return 5;
}

int AbsPath::state2(int c) {
  std::cout << "state2" << std::endl;
  // This is a useless state?
  // TODO remove
  return 2;
}

int AbsPath::state3(int c) {
  std::cout << "state3" << std::endl;
  // Parse the querystring key
  if (c == EOF) {
    return 2;
  } else if (c == '&') {
    // Begin another key (this key has no value)
    return 3;
  } else if (c == '=') {
    // Begin the value
    return 4;
  } else if (httpUtils::isQueryStringSafe((char) c)) {
    return 3;
  }
  FSMError = "Invalid character in querystring";
  return 5;
}

int AbsPath::state4(int c) {
  std::cout << "state4" << std::endl;
  // Parse the querystring value
  if (c == EOF) {
    return 2;
  } else if (c == '&') {
    // Begin new value
    return 3;
  } else if (httpUtils::isQueryStringSafe((char) c)) {
    return 4;
  }
  FSMError = "Invalid character in querystring value";
  return 5;
}

int AbsPath::state5(int c) {
  std::cout << "state5" << std::endl;
  // Error state
  throw FSMError.c_str();
}