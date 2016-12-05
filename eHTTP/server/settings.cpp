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
#include <iostream>
#include "settings.h"
#include "../../EduTLS/src/encoding/base64.h"
#include "../../EduTLS/src/encoding/hex.h"

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
  if (config["tls"]) {
    YAML::Node tlsNode = config["tls"];
    loadTls(tlsNode);
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
uint32_t settings::getBase64ByteLen(std::string base64) {
  uint32_t len;
  if (base64.length() < 4) {
    return 0;
  }
  len = (uint32_t) base64.length() / 4 * 3;
  if (base64[base64.length() - 1] == '=') {
    len--;
  }
  if (base64[base64.length() - 2] == '=') {
    len--;
  }
  return len;
}
void settings::loadTls(YAML::Node &tlsNode) {
  tlsConfiguration = new TLSConfiguration();
  std::string certString;
  uint8_t n[256];
  std::string nString;
  uint8_t e[3];
  std::string eString;
  uint8_t d[256];
  std::string dString;
  if (!tlsNode["cert"]) {
    throw "TLS config missing cert.";
  }
  certString = tlsNode["cert"].as<std::string>();
  if (!tlsNode["n"]) {
    throw "TLS config missing n.";
  }
  nString = tlsNode["n"].as<std::string>();
  if (!tlsNode["e"]) {
    throw "TLS config missing e.";
  }
  eString = tlsNode["e"].as<std::string>();
  if (!tlsNode["d"]) {
    throw "TLS config missing d.";
  }
  dString = tlsNode["d"].as<std::string>();

  tlsConfiguration->debug = true;
  tlsConfiguration->cert.certificate_length = getBase64ByteLen(certString);
  tlsConfiguration->cert.certificate_data = (uint8_t *) malloc(sizeof(uint8_t) * tlsConfiguration->cert.certificate_length);
  fromBase64(tlsConfiguration->cert.certificate_data, (char *) certString.c_str(), certString.length());
  fromHex((uint8_t *) &n, (char *) nString.c_str(), nString.length());
  fromHex((uint8_t *) &e, (char *) eString.c_str(), eString.length());
  fromHex((uint8_t *) &d, (char *) dString.c_str(), dString.length());

  mpz_t key_n;
  mpz_init(key_n);
  mpz_import(key_n, 256, 1, sizeof(uint8_t), 0, 0, n);
  mpz_t key_e;
  mpz_init(key_e);
  mpz_import(key_e, 3, 1, sizeof(uint8_t), 0, 0, e);
  mpz_t key_d;
  mpz_init(key_d);
  mpz_import(key_d, 256, 1, sizeof(uint8_t), 0, 0, d);

  tlsConfiguration->key.exponent(key_e);
  tlsConfiguration->key.priv(key_d);
  tlsConfiguration->key.modulus(key_n);
}
