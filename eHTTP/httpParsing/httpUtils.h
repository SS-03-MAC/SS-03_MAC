//===-- eHTTP/httpParsing/httpUtils.h ---------------------------*- C++ -*-===//
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

#pragma once

#include <istream>
#include <sstream>
#include <iostream>

class httpUtils {
private:
  static const char URI_EXTRA[];
  static const char URI_PCHAR[];
  static const char URI_UNSAFE[];
  static const char URI_SAFE[];
  static const char URL_RESERVED[];

  /// Converts two hex characters to a char.
  static char hexToChar(char c1, char c2);
  /// Converts a hex character to an int.
  /// \throws \"Invalid hex character.\" if the character is outside of the hex range.
  static int hexToInt(char c);
  /// Takes an array of characters, \p c, and searches for \p search in the array.
  static bool charArrayContains(const char *c, int size, char search);

public:
  /// Reads past any Linear WhiteSpace (defined in RFC 2616).
  inline static bool ingestLWS(std::istream *in) {
    bool hasCRLF;
    bool hasWSP;
    hasCRLF = ingestCRLF(in);
    hasWSP = ingestWSP(in) != 0;
    if (!hasWSP && hasCRLF) {
      // CRLF not followed by whitespace, put CRLF back
      in->putback('\n');
      in->putback('\r');
    }
    return hasWSP;
  }

  /// Reads past any WhiteSPace (defined in RFC 2616).
  inline static int ingestWSP(std::istream *in) {
    int count = 0;
    while (isWSP(in->peek())) {
      in->get();
      count++;
    }
    return count;
  }

  /// Reads a \\r\\n if available.
  inline static bool ingestCRLF(std::istream *in) {
    if (in->peek() == '\r') {
      in->get();
      if (in->peek() == '\n') {
        in->get();
        return true;
      } else {
        in->putback('\r');
      }
    }
    return false;
  }

  /// \returns true if \p val\ is WhiteSPace (defined in RFC 2616), otherwise false.
  inline static bool isWSP(int val) {
    return (val == ' ' || val == '\t');
  }

  /// Checks if what's available in \p in is a \\r\\n, but does not move the istream position.
  inline static bool isCRLF(std::istream *in) {
    bool returnVal = false;
    if (in->peek() == '\r') {
      in->get();
      if (in->peek() == '\n') {
        returnVal = true;
      }
      in->putback('\r');
    }
    return returnVal;
  }

  /// Reads a value from \p in.  The value is terminated in LWS, which allows multiline values.
  inline static std::string readUntilEndOfVal(std::istream *in) {
    std::stringstream out;
    bool firstTime = true;
    ingestLWS(in);

    do {
      if (firstTime) {
        firstTime = false;
      } else {
        out << std::endl;
      }
      while (!isCRLF(in)) {
        out << (char) in->get();
      }
    } while (ingestLWS(in) != 0);
    ingestCRLF(in);
    return out.str();
  }

  static bool isQueryStringSafe(char c);
  static bool isUriSafe(char c);
  static bool isUriUnsafe(char c);
  static bool isUriReserved(char c);
  static bool isUriExtra(char c);
  static bool isUriPchar(char c);
  static bool isUriUchar(char c);
  static bool isUriUnreserved(char c);
  static bool isUriNational(char c);

  /// Reads a "token" from \p in.  A "token" ends in any WhiteSPace.
  static std::string readToken(std::istream *in);

  /// Unescapes hex encoded characters.
  static std::string uriDecode(std::string &uri);
  /// Escapes any reserved or unsafe characters in \p uri.
  static std::string uriEncode(std::string &uri);

  /// Compares two strings without reguard to the case.
  static bool equalsCaseInsensitive(std::string &s1, std::string &s2);
};