#include "httpHeaderCollection.h"

httpHeaderCollection::httpHeaderCollection(std::istream &input) {
  int inChar;
  std::string thisLine;
  std::stringstream lineAccumulator;
  bool headersDone = false;

  do {
    std::getline(input, thisLine);
    if (thisLine.length() != 0 && thisLine.back() == '\r') {
      // getLine finds LF (\n), but it should be preceeded by CR (\r), which must be removed.
      thisLine.resize(thisLine.length() - 1);
    }
    if (thisLine.length() == 0) {
      headersDone = true;
    } else {
      this->push_back(new httpHeader(thisLine));
    }
  } while (!headersDone);
}

std::string httpHeaderCollection::toString() {
  std::stringstream out;
  for (size_type i = 0; i < this->size(); i++) {
    out << *this->at(i) << std::endl;
  }
  return out.str();
}
