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

  uint8_t buf[(1 << 16) + 1];
  ssize_t r = read(c, buf, sizeof(buf) - 1);
  std::cout << "Read " << r << " bytes" << std::endl;

  char hex[r * 2 + 1];
  toHex(hex, buf, r);
  hex[r * 2 + 1] = '\0';
  std::cout << "Data:\n" << hex << std::endl;

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
    std::cout << "Decoding plaintext handshake:" << h->decode(p->fragment, p->length) << std::endl;
  }

  close(c);
  close(s);

  return 0;
}
