#include "serverSettings.h"
#include "httpParsing/httpUtils.h"
#include "httpParsing/AbsPath.h"

bool httpServer::settings::getScriptForPath(httpParsing::AbsPath &path, std::string &script) {
  for (int i = 0; i < cgiEndpoints.size(); i++) {
    if (path.beginsWith(cgiEndpoints[i].pathElement)) {
      script = cgiEndpoints[i].cgiPath;
      return true;
    }
  }
  return false;
}
