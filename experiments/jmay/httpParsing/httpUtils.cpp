#include "httpUtils.h"

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
