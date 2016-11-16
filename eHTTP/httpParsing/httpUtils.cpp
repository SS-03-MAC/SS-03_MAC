//===-- eHTTP/httpParsing/httpUtils.cpp -------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains utilities that are helpful for HTTP request and response
/// parsing.
///
//===----------------------------------------------------------------------===//

#include "httpUtils.h"

const char httpUtils::URI_EXTRA[] = {'!', '*', '\'', '(', ')', ','};
const char httpUtils::URI_PCHAR[] = {':', '@', '&', '=', '+'}; // and UCHAR
const char httpUtils::URI_UNSAFE[] = {'\127', ' ', '"', '#', '%', '<', '>'};// and CTL (0 through 31 and DEL(127))
const char httpUtils::URI_SAFE[] = {'$', '-', '_', '.'};
const char httpUtils::URL_RESERVED[] = {';', '/', '?', ':', '@', '&', '=', '+'};

char httpUtils::hexToChar(char c1, char c2) {
  return (char) ((hexToInt(c1) << 4) + hexToInt(c2));
}

int httpUtils::hexToInt(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <= 'f') {
    return (c - 'a') + 10;
  }
  if (c >= 'A' && c <= 'F') {
    return (c - 'A') + 10;
  }
  throw "Invalid hex character.";
}

bool httpUtils::charArrayContains(const char *c, int size, char search) {
  for (int i = 0; i < size; i++) {
    if (c[i] == search) {
      return true;
    }
  }
  return false;
}

std::string httpUtils::readToken(std::istream *in) {
  std::stringstream out;
  int read;
  bool endOfToken = false;
  ingestWSP(in);
  do {
    read = in->get();
    if (read == EOF) {
      endOfToken = true;
    } else if (isWSP(read)) {
      endOfToken = true;
    } else {
      out << (char) read;
    }
  } while (!endOfToken);
  ingestWSP(in);
  return out.str();
}

bool httpUtils::isQueryStringSafe(char c) {
  return isUriUchar(c) || isUriReserved(c);
}

bool httpUtils::isUriSafe(char c) {
  return charArrayContains(URI_SAFE, sizeof(URI_SAFE), c);
}

bool httpUtils::isUriUnsafe(char c) {
  if (c < 32) {
    return true;
  }
  for (unsigned int i = 0; i < sizeof(URI_UNSAFE); i++) {
    if (c == URI_UNSAFE[i]) {
      return true;
    }
  }
  return false;
}

bool httpUtils::isUriReserved(char c) {
  for (unsigned int i = 0; i < sizeof(URL_RESERVED); i++) {
    if (c == URL_RESERVED[i]) {
      return true;
    }
  }
  return false;
}

bool httpUtils::isUriExtra(char c) {
  return charArrayContains(URI_EXTRA, sizeof(URI_EXTRA), c);
}

bool httpUtils::isUriPchar(char c) {
  return isUriUchar(c) || charArrayContains(URI_PCHAR, sizeof(URI_PCHAR), c);
}

bool httpUtils::isUriUchar(char c) {
  // Warning: this is a partial check! The next two characters should be checked if it's escaped ('%').
  return isUriUnreserved(c) || c == '%';
}

bool httpUtils::isUriUnreserved(char c) {
  return isalnum(c) || isUriSafe(c) || isUriExtra(c) || isUriNational(c);
}

bool httpUtils::isUriNational(char c) {
  return !(isalnum(c) || isUriReserved(c) || isUriExtra(c) || isUriSafe(c) || isUriUnsafe(c));
}

std::string httpUtils::uriDecode(std::string &uri) {
  std::stringstream decoded;
  for (unsigned int i = 0; i < uri.length(); i++) {
    switch (uri[i]) {
    case '%':
      // Validate % HEX HEX
      if (i + 2 < uri.length()) {
        if (isxdigit(uri[i + 1]) && isxdigit(uri[i + 2])) {
          char decodedChar = hexToChar(uri[i + 1], uri[i + 2]);
          decoded << decodedChar;
          i += 2;
          break;
        }
      }
      // Intentional flow to default case
    default:decoded << uri[i];
    }
  }
  return decoded.str();
}

std::string httpUtils::uriEncode(std::string &uri) {
  std::stringstream out;
  for (unsigned int i = 0; i < uri.length(); i++) {
    if (isUriReserved(uri[i]) || isUriUnsafe(uri[i])) {
      out << '%';
      out << std::hex << (int) uri[i];
    } else {
      out << uri[i];
    }
  }
  return out.str();
}

bool httpUtils::equalsCaseInsensitive(std::string &s1, std::string &s2) {
  if (s1.size() != s2.size()) {
    return false;
  }
  for (int i = 0; i < s1.size(); i++) {
    if (tolower(s1[i]) != tolower(s2[i])) {
      return false;
    }
  }
  return true;
}