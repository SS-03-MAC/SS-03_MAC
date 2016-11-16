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

#include "settings.h"

using namespace eHTTP::server;

bool settings::getScriptForPath(httpParsing::AbsPath &path, cgiEndpoint_t &cgiEndpoint) {
  for (int i = 0; i < cgiEndpoints.size(); i++) {
    if (path.beginsWith(cgiEndpoints[i].pathElement)) {
      cgiEndpoint = cgiEndpoints[i];
      return true;
    }
  }
  return false;
}
