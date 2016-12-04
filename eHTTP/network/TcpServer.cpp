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
#include "../../EduTLS/src/tls/api/TLSServer.h"

namespace network {

int tcp_start(uint16_t port) {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  int optval = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

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

long long write_stream(int netStreamFd, std::istream &inStream) {
  char buffer[1024];
  long long count = 0;
  while (!inStream.eof()) {
    inStream.read(buffer, sizeof(buffer));
    write(netStreamFd, buffer, (unsigned int) inStream.gcount());
    count += inStream.gcount();
  }
  return count;
}

long long write_stream_tls(TLSServer &client, std::istream &inStream) {
  char buffer[1024];
  long long count = 0;
  while (!inStream.eof()) {
    inStream.read(buffer, sizeof(buffer));
    client.Write((uint8_t *) buffer, (size_t) inStream.gcount());
    count += inStream.gcount();
  }
  return count;
}

long long passData(std::istream &tcpIstream,
                 int *clientFd,
                 int cgiStdout,
                 int cgiStdin,
                 size_t requestContentLen,
                 size_t bufSize) {
  ssize_t r;
  long long total = 0;
  char buffer[bufSize];
  ssize_t toRead;
  // TCP in
  while (requestContentLen > 0) {
    // toRead = min(requestContentLen, bufSize)
    toRead = requestContentLen > bufSize ? bufSize : requestContentLen;
    tcpIstream.read(buffer, toRead);
    write(cgiStdin, buffer, (size_t) tcpIstream.gcount());
    requestContentLen -= tcpIstream.gcount();
  }

  // CGI in
  r = read(cgiStdout, buffer, bufSize);
  do {
    // TCP out
    total += r;
    write(*clientFd, buffer, (size_t) r);
    r = read(cgiStdout, buffer, bufSize);
  } while (r > 0);
  return total;
}

long long passDataTls(std::istream &tcpIstream,
                      TLSServer *client,
                      int cgiStdout,
                      int cgiStdin,
                      size_t requestContentLen,
                      size_t bufSize) {
  ssize_t r;
  long long total = 0;
  char buffer[bufSize];
  ssize_t  toRead;
  // TCP in
  while (requestContentLen > 0) {
    toRead = requestContentLen > bufSize ? bufSize : requestContentLen;
    tcpIstream.read(buffer, toRead);

    buffer[tcpIstream.gcount()] = 0;

    client->Write((uint8_t *) buffer, (size_t) tcpIstream.gcount());
    requestContentLen -= tcpIstream.gcount();
  }

  // CGI in
  r = read(cgiStdout, buffer, bufSize);
  do {
    // TCP out
    total += r;
    client->Write((uint8_t *) buffer, (size_t) r);
    r = read(cgiStdout, buffer, bufSize);
  } while (r > 0);
  return total;
}

}
