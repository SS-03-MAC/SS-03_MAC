#include <iostream>
#include <fstream>
#include <cstring>

#include "httpParsing/httpRequestHeaderCollection.h"
#include "server/settings.h"
#include "../EduTLS/src/crypto/crypto.h"
#include "../EduTLS/src/encoding/encoding.h"
#include "../EduTLS/src/tls/tls.h"
#include "server/server.h"

int main(int argc, char *argv[]) {
  std::string configPath;
  eHTTP::server::server *server;
  eHTTP::server::settings *settings;
  if (argc > 1) {
    configPath = argv[1];
  } else {
    configPath = "eHTTP/config.yaml";
  }
  try {
    settings = new eHTTP::server::settings(configPath);
  } catch (const char *err) {
    std::cout << "Error loading settings: " << err << std::endl;
    return 1;
  }

  server = new eHTTP::server::server(*settings);

  server->serve();
}
