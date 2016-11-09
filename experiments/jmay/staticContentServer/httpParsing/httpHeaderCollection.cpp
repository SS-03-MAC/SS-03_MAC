#include "httpHeaderCollection.h"
#include "httpUtils.h"

httpHeaderCollection::httpHeaderCollection(std::istream *input) {
  bool headersDone = false;

  // Store the first line for subclasses to parse.  We can't call a virtual function in the constructor.
  getLineAndTrim(*input, firstLine);

  // Parse headers
  do {
    if (httpUtils::isCRLF(input)) {
      headersDone = true;
      httpUtils::ingestCRLF(input);
    } else {
      this->push_back(new httpHeader(input));
    }
  } while (!headersDone);
}

httpHeaderCollection::httpHeaderCollection(std::string httpVersion) {
  this->httpVersion = httpVersion;
}

std::string httpHeaderCollection::toString() {
  std::stringstream out;
  // Virtual toString for subclass specific first line
  out << firstLineToString() << "\r\n";
  // Headers
  for (size_type i = 0; i < this->size(); i++) {
    out << *this->at(i) << "\r\n";
  }
  out << "\r\n";
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
void httpHeaderCollection::getLineAndTrim(std::istream &input, std::string &out) {
  std::getline(input, out);
  httpHeaderCollection::trimTrailingCR(out);
}

int64_t httpHeaderCollection::getInt64Value(std::string key) {
  for (int i = 0; i < this->size(); i++) {
    if (httpUtils::equalsCaseInsensitive((*this)[i]->key, key)) {
      // TODO is this safe?
      return atoll((*this)[i]->value.c_str());
    }
  }
  throw "Key not found";
}

bool httpHeaderCollection::keyExists(std::string key) {
  for (int i = 0; i < this->size(); i++) {
    if (httpUtils::equalsCaseInsensitive((*this)[i]->key, key)) {
      return true;
    }
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, httpHeaderCollection &headerCollection) {
  return os << headerCollection.toString();
}