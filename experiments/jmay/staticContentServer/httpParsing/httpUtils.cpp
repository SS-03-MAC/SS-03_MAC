#include "httpUtils.h"

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

bool httpUtils::isUriUnsafe(char c) {
  if (c < 32) {
    return true;
  }
  for (int i = 0; i < sizeof(URI_UNSAFE); i++) {
    if (c == URI_UNSAFE[i]) {
      return true;
    }
  }
  return false;
}

bool httpUtils::isUriReserved(char c) {
  for (int i = 0; i < sizeof(URL_RESREVED); i++) {
    if (c == URL_RESREVED[i]) {
      return true;
    }
  }
  return false;
}

std::string httpUtils::uriDecode(std::string &uri) {
  std::stringstream decoded;
  for (int i = 0; i < uri.length(); i++) {
    switch (uri[i]) {
    case '%':
      // Validate % HEX HEX
      if (i + 2 < uri.length()) {
        if (isxdigit(i + 1) && isxdigit(i + 2)) {
          char decodedChar = hexToChar(uri[i], uri[i + 1]);
          // Refuse unsafe and reserved characters
          if (!isUriUnsafe(decodedChar) && !isUriReserved(decodedChar)) {
            decoded << decodedChar;
            i += 2;
            break;
          } else {
            throw "Unsafe URI";
          }
        }
      }
      // Intentional flow to default case
    default:
      decoded << uri[i];
    }
  }
  return decoded.str();
}

std::string httpUtils::uriEncode(std::string &uri) {
  std::stringstream out;
  for (int i = 0; i < uri.length(); i++) {
    if (isUriReserved(uri[i]) || isUriUnsafe(uri[i])) {
      out << '%';
      out << std::hex << (int) uri[i];
    } else {
      out << uri[i];
    }
  }
  return out.str();
}