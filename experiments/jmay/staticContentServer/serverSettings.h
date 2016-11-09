#pragma once

#include <vector>
#include <string>
#include "httpParsing/AbsPath.h"
namespace httpServer {

struct cgiEndpoint_t {
  std::string pathElement;
  std::string cgiPath;
};

class settings {
public:
  std::vector<std::string> defaultDocuments;
  uint16_t port;
  std::string basePath;
  std::vector<struct cgiEndpoint_t> cgiEndpoints;
  bool getScriptForPath(httpParsing::AbsPath &path, std::string &script);
};

}