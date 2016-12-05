#include <iostream>
#include <fstream>
#include <cstring>

#include "httpParsing/httpRequestHeaderCollection.h"
#include "server/settings.h"
#include "../EduTLS/src/crypto/crypto.h"
#include "../EduTLS/src/encoding/encoding.h"
#include "../EduTLS/src/tls/tls.h"
#include "server/server.h"

void initTls();

TLSConfiguration *tlsConfig;

int main(int argc, char *argv[]) {
  initTls();
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


  /*server = new eHTTP::server::server(8000, basePath);
  server->addDefaultDocument("test2.txt");

  server->addCgiEndpoint("api", "dotnet", "C:\\Users\\mburket\\Source\\Repos\\SS-03_MAC\\MAC\\src\\MAC\\bin\\Debug\\netcoreapp1.0\\publish\\MAC.dll");
  server->addCgiEndpoint("env", "printenv", "");
  server->setTlsConfiguration(tlsConfig);*/

  server = new eHTTP::server::server(*settings, *tlsConfig);

  server->serve();
}

void initTls() {
  tlsConfig = new TLSConfiguration();
  tlsConfig->debug = true;
  tlsConfig->cert.certificate_length = 806;
  tlsConfig->cert.certificate_data = (uint8_t *) malloc(sizeof(uint8_t) * 806);
  std::string cert =
      "MIIDIjCCAgoCCQCAHbmNOfRXmTANBgkqhkiG9w0BAQsFADBTMQswCQYDVQQGEwJVUzENMAsGA1UECAwESW93YTENMAsGA1UEBwwEQW1lczESMBAG"
          "A1UECgwJQ09NIFMgMzA5MRIwEAYDVQQDDAlsb2NhbGhvc3QwHhcNMTYxMDMwMTgyODEzWhcNMTkwODIwMTgyODEzWjBTMQswCQYDVQQGEwJVUzEN"
          "MAsGA1UECAwESW93YTENMAsGA1UEBwwEQW1lczESMBAGA1UECgwJQ09NIFMgMzA5MRIwEAYDVQQDDAlsb2NhbGhvc3QwggEiMA0GCSqGSIb3DQEB"
          "AQUAA4IBDwAwggEKAoIBAQCewIyjZu97WCTp/TqwT4cZX1OLYUwRyPKFHlmHgDjCU3ZBf2KK155xopkl+TnejKsblupAOI26f19H6/"
          "FV+qPMO5i9s3oRFl6+dIQKMVPr3VH0cQmOFWYYETHrZwFbCHbkuWEsVq4ArBrmwFRinE9ByGx/YBfZlVy0a1ZVC/ZBVDmAD2TJShPd0SeGl/"
          "YlRJ8Fo54BoZWOZP06yWetfK0QtPehOr9231gNP3t0lxEZeum76c73Dfs55IbjSEg/Aq1NLT8R9JFBeHOao/B94N/"
          "trvs7QLc3RPCWX7yR61rmpo2nw+1RYW6wA/Uy/ZMDx3sXQaMB1sNgB3wuQVFBUgptAgMBAAEwDQYJKoZIhvcNAQELBQADggEBAH6L/"
          "7NL48Yn1E6DR5AXRI9J2upKIkXtMYc6+2fDniffiwCkWvUYpKZe1vLAwfIZltAukoZatVmTT7Kc0WlyS2QXeTifnQdZkAE5jpnN2sJ6vOw2VE3G/"
          "rvAflX55TbgXx7P8PGchRHqlR6jO/HQF9A4+kBBQ0kj8QbOt//pQEca85wHEoS37k4Zon/bnV89QnZg0RaGCzlEo/"
          "+KculJP9XLwmNH2NknScz7x3/"
          "FeMWEvjGJGq0MyZx15W6w6EgnUTKGQDmrBMGuL8TSUvGLkidQ6b797uw1rO8ccaZCB6R2OcySdwXUv3Rs+"
          "kod1YVXpeV9aQz2zOPIhqqc0fFxPhc=";
  fromBase64(tlsConfig->cert.certificate_data, (char *) cert.c_str(), 1076);

  uint8_t n[256] = {
      0x9e, 0xc0, 0x8c, 0xa3, 0x66, 0xef, 0x7b, 0x58, 0x24, 0xe9, 0xfd, 0x3a, 0xb0, 0x4f, 0x87, 0x19, 0x5f, 0x53, 0x8b,
      0x61, 0x4c, 0x11, 0xc8, 0xf2, 0x85, 0x1e, 0x59, 0x87, 0x80, 0x38, 0xc2, 0x53, 0x76, 0x41, 0x7f, 0x62, 0x8a, 0xd7,
      0x9e, 0x71, 0xa2, 0x99, 0x25, 0xf9, 0x39, 0xde, 0x8c, 0xab, 0x1b, 0x96, 0xea, 0x40, 0x38, 0x8d, 0xba, 0x7f, 0x5f,
      0x47, 0xeb, 0xf1, 0x55, 0xfa, 0xa3, 0xcc, 0x3b, 0x98, 0xbd, 0xb3, 0x7a, 0x11, 0x16, 0x5e, 0xbe, 0x74, 0x84, 0x0a,
      0x31, 0x53, 0xeb, 0xdd, 0x51, 0xf4, 0x71, 0x09, 0x8e, 0x15, 0x66, 0x18, 0x11, 0x31, 0xeb, 0x67, 0x01, 0x5b, 0x08,
      0x76, 0xe4, 0xb9, 0x61, 0x2c, 0x56, 0xae, 0x00, 0xac, 0x1a, 0xe6, 0xc0, 0x54, 0x62, 0x9c, 0x4f, 0x41, 0xc8, 0x6c,
      0x7f, 0x60, 0x17, 0xd9, 0x95, 0x5c, 0xb4, 0x6b, 0x56, 0x55, 0x0b, 0xf6, 0x41, 0x54, 0x39, 0x80, 0x0f, 0x64, 0xc9,
      0x4a, 0x13, 0xdd, 0xd1, 0x27, 0x86, 0x97, 0xf6, 0x25, 0x44, 0x9f, 0x05, 0xa3, 0x9e, 0x01, 0xa1, 0x95, 0x8e, 0x64,
      0xfd, 0x3a, 0xc9, 0x67, 0xad, 0x7c, 0xad, 0x10, 0xb4, 0xf7, 0xa1, 0x3a, 0xbf, 0x76, 0xdf, 0x58, 0x0d, 0x3f, 0x7b,
      0x74, 0x97, 0x11, 0x19, 0x7a, 0xe9, 0xbb, 0xe9, 0xce, 0xf7, 0x0d, 0xfb, 0x39, 0xe4, 0x86, 0xe3, 0x48, 0x48, 0x3f,
      0x02, 0xad, 0x4d, 0x2d, 0x3f, 0x11, 0xf4, 0x91, 0x41, 0x78, 0x73, 0x9a, 0xa3, 0xf0, 0x7d, 0xe0, 0xdf, 0xed, 0xae,
      0xfb, 0x3b, 0x40, 0xb7, 0x37, 0x44, 0xf0, 0x96, 0x5f, 0xbc, 0x91, 0xeb, 0x5a, 0xe6, 0xa6, 0x8d, 0xa7, 0xc3, 0xed,
      0x51, 0x61, 0x6e, 0xb0, 0x03, 0xf5, 0x32, 0xfd, 0x93, 0x03, 0xc7, 0x7b, 0x17, 0x41, 0xa3, 0x01, 0xd6, 0xc3, 0x60,
      0x07, 0x7c, 0x2e, 0x41, 0x51, 0x41, 0x52, 0x0a, 0x6d};
  uint8_t e[3] = {0x01, 0x00, 0x01};
  uint8_t d[256] = {
      0x35, 0x9a, 0x8c, 0xa2, 0x6c, 0x12, 0x77, 0x12, 0x97, 0x3c, 0x4f, 0x1e, 0x2f, 0x04, 0x5b, 0x78, 0xcc, 0xc0, 0x57,
      0xf2, 0xdd, 0x8d, 0xaf, 0xcd, 0x7b, 0xf7, 0x78, 0x81, 0x91, 0x61, 0x18, 0xf4, 0xb7, 0x9c, 0x7c, 0x17, 0xd9, 0x0b,
      0xdf, 0x5b, 0x3d, 0x6c, 0xfa, 0xee, 0x81, 0x84, 0xcc, 0xf8, 0xc5, 0xd3, 0x1a, 0x7b, 0xde, 0xdc, 0xb4, 0x59, 0x67,
      0xe1, 0xd0, 0x20, 0x68, 0x48, 0xbe, 0x60, 0x2a, 0xcb, 0x73, 0x5a, 0x93, 0xe0, 0x0b, 0x2e, 0xa8, 0x9e, 0x8d, 0x2b,
      0x27, 0xe6, 0xcf, 0x60, 0xa6, 0xd8, 0xa4, 0x06, 0x76, 0xec, 0x70, 0xd1, 0xb5, 0x94, 0xa6, 0x88, 0xdc, 0x63, 0x51,
      0xa3, 0x5b, 0xad, 0xe0, 0xca, 0xe8, 0xe5, 0xce, 0x22, 0x4e, 0xdf, 0x15, 0x98, 0x28, 0xc7, 0xe0, 0xd7, 0x34, 0x86,
      0xb6, 0x27, 0xcb, 0x45, 0xd3, 0xf2, 0x3e, 0x95, 0x73, 0xcc, 0x39, 0xc2, 0xc7, 0xe1, 0xd1, 0x72, 0x3f, 0x5e, 0x4e,
      0x83, 0x61, 0x44, 0x84, 0x17, 0xcc, 0xfc, 0x8e, 0x27, 0x7d, 0x86, 0x09, 0xb3, 0x5a, 0xb7, 0x25, 0x7e, 0x9e, 0xa0,
      0xc2, 0xc7, 0x8a, 0x10, 0x5c, 0xef, 0x15, 0x71, 0x77, 0x01, 0x76, 0x51, 0xdd, 0x65, 0x92, 0x2c, 0x94, 0xdc, 0x44,
      0xf8, 0x9a, 0x3c, 0xa3, 0x1c, 0x26, 0xbb, 0xff, 0x63, 0x5f, 0xb5, 0xa8, 0x89, 0x4d, 0x48, 0x24, 0xdd, 0xc9, 0xe4,
      0x26, 0x6b, 0xe4, 0xe9, 0x86, 0x77, 0x32, 0x81, 0x45, 0xfb, 0xa3, 0xc8, 0x81, 0x87, 0x75, 0x37, 0x92, 0xa4, 0xd8,
      0x06, 0x92, 0x43, 0x6e, 0x80, 0x0d, 0x4c, 0x75, 0x29, 0x28, 0x6b, 0xc2, 0xc2, 0x9d, 0xe4, 0x84, 0x02, 0x8a, 0x09,
      0x38, 0xe7, 0x84, 0x73, 0x97, 0x51, 0x57, 0x4b, 0x72, 0x81, 0x5b, 0x1a, 0x20, 0xac, 0x2c, 0x0d, 0xd6, 0xb0, 0xde,
      0xb0, 0x5d, 0x5f, 0x81, 0xc8, 0xd7, 0x1e, 0xd3, 0x3d};

  mpz_t key_n;
  mpz_init(key_n);
  mpz_import(key_n, 256, 1, sizeof(uint8_t), 0, 0, n);
  mpz_t key_e;
  mpz_init(key_e);
  mpz_import(key_e, 3, 1, sizeof(uint8_t), 0, 0, e);
  mpz_t key_d;
  mpz_init(key_d);
  mpz_import(key_d, 256, 1, sizeof(uint8_t), 0, 0, d);

  tlsConfig->key.exponent(key_e);
  tlsConfig->key.priv(key_d);
  tlsConfig->key.modulus(key_n);
}
