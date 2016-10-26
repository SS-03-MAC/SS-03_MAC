#pragma once

#include <istream>
#include <sstream>
//#include <sstream>
class httpUtils {
public:
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

  inline static int ingestWSP(std::istream *in) {
    int count = 0;
    while (isWSP(in->peek())) {
      in->get();
      count++;
    }
    return count;
  }

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

  inline static bool isWSP(int val) {
    return (val == ' ' || val == '\t');
  }

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

  inline static std::string readUntilEndOfVal(std::istream *in) {
    std::stringstream out;
    bool headerDone = false;
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

  static std::string readToken(std::istream *in);
};