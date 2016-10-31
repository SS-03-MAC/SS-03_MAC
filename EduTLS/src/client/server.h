#include "../encoding/hex.h"
#include "../tls/tls.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cstring>
#include <iostream>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

inline int serve() {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  int optval = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8443);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (s == -1) {
    return -1;
  }

  int b = bind(s, (struct sockaddr *)&addr, sizeof(addr));
  int l = listen(s, 1);
  struct sockaddr_in client_addr;
  std::cout << "Waiting for client..." << std::endl;
  std::cout << b << l << std::endl;
  if (b == -1 || l == -1) {
    return -1;
  }

  socklen_t *clilen = (socklen_t *)sizeof(client_addr);
  int c = accept(s, (sockaddr *)&client_addr, (socklen_t *)&clilen);

  TLSConfiguration *config = new TLSConfiguration();
  config->debug = true;
  config->cert.certificate_length = 806;
  config->cert.certificate_data = (uint8_t *)malloc(sizeof(uint8_t) * 806);
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
  fromBase64(config->cert.certificate_data, (char *)cert.c_str(), 1076);

  TLSServer *srv = new TLSServer(config);
  srv->AcceptClient(c);
  srv->Handshake();

  delete srv;
  delete config;

  /*
  uint8_t buf[(1 << 16) + 1];
  ssize_t r = read(c, buf, sizeof(buf) - 1);
  std::cout << "Read " << r << " bytes" << std::endl;

  char hex[r * 2 + 1];
  toHex(hex, buf, r);
  hex[r * 2 + 1] = '\0';
  std::cout << "Data:\n" << hex << std::endl << std::endl;

  TLSPlaintext *p = new TLSPlaintext();
  TLSCompressed *cp = new TLSCompressed(p);
  GenericStreamCipher *gsc = new GenericStreamCipher(cp);
  TLSCiphertext *ct = new TLSCiphertext(gsc);

  std::cout << "Decoding encrypted message: " << ct->decode(buf, r) << std::endl;

  std::cout << "Received message: " << std::endl;
  std::cout << "\tMessage type: " << static_cast<int>(ct->type) << std::endl;
  std::cout << "\tProtocol Version: " << (int)ct->version.major << "." << (int)ct->version.minor << std::endl;
  std::cout << "\tLength: " << ct->length << std::endl;

  if (ct->type == ContentType_e::handshake) {
    HandshakeType *h = new HandshakeType();
    std::cout << "\tDecoding plaintext handshake:" << h->decode(p->fragment, p->length) << std::endl;
    std::cout << "\t\tMessage type: " << static_cast<int>(h->type) << std::endl;
    std::cout << "\t\tLength: " << h->length << std::endl;

    if (h->type == HandshakeType_e::client_hello) {
      ClientHello *ch = (ClientHello *)h->body;
      std::cout << "\t\tDecoding client_hello:" << std::endl;
      std::cout << "\t\t\tClient Version: " << (int)ch->client_version.major << "." << (int)ch->client_version.minor
                << std::endl;
      std::cout << "\t\t\tClient Random (date): " << ch->random.gmt_unix_time << std::endl;
      toHex(hex, ch->random.random_bytes, 28);
      hex[56] = '\0';
      std::cout << "\t\t\tClient Random (data): " << hex << std::endl;
      toHex(hex, ch->session_id, ch->session_id_length);
      hex[2 * ch->session_id_length] = '\0';
      std::cout << "\t\t\tClient Session ID (" << ch->session_id_length << "): " << hex << std::endl;
    }
  }*/

  close(b);
  close(c);
  close(s);

  return 0;
}
