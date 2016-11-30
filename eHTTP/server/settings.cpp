//===-- eHTTP/httpServer/settings.cpp ---------------------------*- C++ -*-===//
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

#include <yaml-cpp/yaml.h>
#include "settings.h"

using namespace eHTTP::server;

cgiEndpoint_t settings::mapToEndpoint(YAML::Node map) {
  cgiEndpoint_t ep;
  if (!map["pathElement"]) {
    throw "pathElement is required in cgiEndpoint.";
  }
  if (!map["cgiPath"]) {
    throw "cgiPath is required in cgiEndpoint.";
  }

  ep.pathElement = map["pathElement"].as<std::string>();
  ep.cgiPath = map["cgiPath"].as<std::string>();
  if (map["cgiArguments"]) {
    ep.cgiArguments = map["cgiArguments"].as<std::string>();
  }
  return ep;
}

settings::settings(std::string yamlConfigPath) {
  YAML::Node config;
  try {
     config = YAML::LoadFile(yamlConfigPath);
  } catch (YAML::ParserException err) {
    throw err.what();
  } catch (YAML::BadFile err) {
    throw err.what();
  }

  // TODO catch type conversion errors
  if (config["port"]) {
    port = config["port"].as<uint16_t>();
  } else {
    port = 80;
  }
  if (config["portTls"]) {
    portTls = config["portTls"].as<uint16_t>();
  } else {
    portTls = 443;
  }
  if (config["basePath"]) {
    basePath = config["basePath"].as<std::string>();
  } else {
    basePath = "/var/www";
  }
  if (config["cgiEndpoints"]) {
    switch (config["cgiEndpoints"].Type()) {
    case YAML::NodeType::Map:
      cgiEndpoints.push_back(mapToEndpoint(config["cgiEndpoints"]));
      break;
    case YAML::NodeType::Sequence: {
      YAML::Node yamlEndpoints = config["cgiEndpoints"];
      for (YAML::const_iterator it = yamlEndpoints.begin(); it != yamlEndpoints.end(); it++) {
        cgiEndpoints.push_back(mapToEndpoint(*it));
      }
    }
      break;
    default:
      throw "cgiEndpoints must be a sequence or map.";
    }
  }
  if (config["defaultDocuments"]) {
    switch (config["defaultDocuments"].Type()) {
    case YAML::NodeType::Scalar:
      defaultDocuments.push_back(config["defaultDocuments"].as<std::string>());
      break;
    case YAML::NodeType::Sequence: {
      YAML::Node yamlDDocuments = config["defaultDocuments"];
      for (YAML::const_iterator it = yamlDDocuments.begin(); it != yamlDDocuments.end(); it++) {
        defaultDocuments.push_back(it->as<std::string>());
      }
    }
      break;
    default:
      throw "defaultDocuments must be a sequence or scalar.";
    }
  }
}

bool settings::getScriptForPath(httpParsing::AbsPath &path, cgiEndpoint_t &cgiEndpoint) {
  for (int i = 0; i < cgiEndpoints.size(); i++) {
    if (path.beginsWith(cgiEndpoints[i].pathElement)) {
      cgiEndpoint = cgiEndpoints[i];
      return true;
    }
  }
  return false;
}
