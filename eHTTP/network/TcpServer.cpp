//===-- eHTTP/network/TcpServer.cpp -----------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains methods for working with the TCP sockets.
///
//===----------------------------------------------------------------------===//

#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>
#include <unistd.h>

#include "TcpServer.h"

namespace network {

int tcp_start(uint16_t port) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  bind(s, (struct sockaddr *) &addr, sizeof(addr));
  listen(s, 1);
  return s;
}

int tcp_accept(int sockfd) {
  struct sockaddr_in client_addr;
  socklen_t *clilen = (socklen_t *) sizeof(client_addr);
  std::cout << "Waiting for client..." << std::endl;
  // TODO use select() to also listen for sigkill.
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
