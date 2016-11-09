#include "serverSettings.h"
#include "httpParsing/httpUtils.h"
#include "httpParsing/AbsPath.h"

bool httpServer::settings::getScriptForPath(httpParsing::AbsPath &path, httpServer::cgiEndpoint_t &cgiEndpoint) {
  for (int i = 0; i < cgiEndpoints.size(); i++) {
    if (path.beginsWith(cgiEndpoints[i].pathElement)) {
      cgiEndpoint = cgiEndpoints[i];
      return true;
    }
  }
  return false;
}
