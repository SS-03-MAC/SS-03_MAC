//
// Created by JoelM on 2016-10-03.
//

#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "TcpServer.h"

namespace network {

int tcp_start() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  bind(s, (struct sockaddr *) &addr, sizeof(addr));
  listen(s, 1);
  return s;
}

int tcp_accept(int sockfd) {
  struct sockaddr_in client_addr;
  socklen_t *clilen = (socklen_t *) sizeof(client_addr);
  std::cout << "Waiting for client..." << std::endl;
  int c = accept(sockfd, (sockaddr *) &client_addr, (socklen_t *) &clilen);
  std::cout << "Client connected from " << htonl(client_addr.sin_addr.s_addr) << std::endl;

  return c;
}

int write_stream(int netStreamFd, std::istream &inStream) {
  char buffer[1024];
  int count = 0;
  while (!inStream.eof()) {
    inStream.read(buffer, sizeof(buffer));
    write(netStreamFd, buffer, (unsigned int) inStream.gcount());
    count += inStream.gcount();
  }
  return count;
}

}
