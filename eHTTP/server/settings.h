//===-- eHTTP/httpServer/settings.h -----------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a class for server settings.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

#include "../httpParsing/AbsPath.h"

namespace eHTTP {
namespace server {

/// Represents a single CGI endpoint mapping.
struct cgiEndpoint_t {
  /// The path element that requests start with to match.
  std::string pathElement;
  /// The path to the CGI script/executable.
  std::string cgiPath;
  // TODO change this to a NULL-terminated array.
  /// The arguments to pass to CGI script/executable.
  std::string cgiArguments;
};

/// The settings for the HTTP server.
class settings {
private:
  /// Parses a yaml map into a \p cgiEndpoint_t
  static cgiEndpoint_t mapToEndpoint(YAML::Node map);
public:
  /// Constructs a default \p settings object.
  inline settings() {};
  /// Loads settings from the yaml file specified.
  /// \param yamlConfigPath the path to the yaml configuration file.
  settings(std::string yamlConfigPath);

  /// A vector of default documents to search when a client requests a path.
  std::vector<std::string> defaultDocuments;
  // TODO this should be a vector.
  /// The port for the HTTP server to listen on.
  uint16_t port;
  // TODO this should be a vector.
  /// The port for the HTTP server to listen for TLS clients.
  uint16_t portTls;
  /// The path on the filesystem to serve static content from.
  std::string basePath;
  /// A vector of CGI endpoint mappings.
  std::vector<struct cgiEndpoint_t> cgiEndpoints;
  /// Gets the CGI endpoint that \p path maps to, if it does.
  /// \returns true if a CGI endpoint exists for the path.
  bool getScriptForPath(httpParsing::AbsPath &path, eHTTP::server::cgiEndpoint_t &cgiEndpoint);
};

}
}