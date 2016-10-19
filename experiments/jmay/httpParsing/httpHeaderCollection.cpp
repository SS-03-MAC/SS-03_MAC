#include "httpHeaderCollection.h"

httpHeaderCollection::httpHeaderCollection(std::istream &input) {
  int inChar;
  std::string thisLine;
  std::stringstream lineAccumulator;
  bool headersDone = false;

  // Parse status and HTTP version
  httpHeaderCollection::getlineAndTrim(input, thisLine);
  parseHeaders(thisLine);

  // Parse headers
  do {
    httpHeaderCollection::getlineAndTrim(input, thisLine);
    if (thisLine.length() == 0) {
      headersDone = true;
    } else {
      this->push_back(new httpHeader(thisLine));
    }
  } while (!headersDone);
}

httpHeaderCollection::httpHeaderCollection(std::string httpVersion, int statusVal, std::string statusDescription) {
  this->httpVersion = httpVersion;
  this->statusVal = statusVal;
  this->statusDescription = statusDescription;
}

std::string httpHeaderCollection::toString() {
  std::stringstream out;
  // Status
  out << httpVersion << " " << statusVal << " " << statusDescription << std::endl;
  // Headers
  for (size_type i = 0; i < this->size(); i++) {
    out << *this->at(i) << std::endl;
  }
  out << std::endl;
  return out.str();
}

int httpHeaderCollection::trimTrailingCR(std::string &toTrim) {
  if (toTrim.length() != 0 && toTrim.back() == '\r') {
    // getLine finds LF (\n), but it should be preceeded by CR (\r), which must be removed.
    toTrim.resize(toTrim.length() - 1);
    return 1;
  }
  return 0;
}
void httpHeaderCollection::getlineAndTrim(std::istream &input, std::string &out) {
  std::getline(input, out);
  httpHeaderCollection::trimTrailingCR(out);
}

void httpHeaderCollection::parseHeaders(std::string &headerLine) {
  unsigned long versionEnd = headerLine.find(' ', 0);
  unsigned long statusValEnd = headerLine.find(' ', versionEnd + 1);
  // Parse HTTP version
  httpVersion = headerLine.substr(0, versionEnd);
  // Parse status val
  statusVal = std::stoi(headerLine.substr(versionEnd + 1, statusValEnd - versionEnd - 1));
  // Parse status string
  statusDescription = headerLine.substr(statusValEnd + 1, std::string::npos);
}

std::ostream &operator<<(std::ostream &os, httpHeaderCollection &headerCollection) {
  return os << headerCollection.toString();
}