//
// Created by JoelM on 2016-10-03.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include "pexec.h"
#include "TcpServer.h"

int connectClient(int clientFd);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char *argv[]) {
  int serverFd = tcp_start();
  int clientFd;
  while (1) {
    clientFd = tcp_accept(serverFd);
    if (clientFd == -1) {
      std::cout << "Error accepting client: " << errno << std::endl;
    } else {
      connectClient(clientFd);
    }
  }
}
#pragma clang diagnostic pop

int connectClient(int clientFd) {
  char buf[1024];
  ssize_t r;
  r = read(clientFd, buf, sizeof(buf));
  buf[r] = '\0';
  std::cout << buf << std::endl;
  const char *out = "HTTP/1.1 200 OK\r\n\r\nHello world\r\n";
  write(clientFd, out, strlen(out));
  close(clientFd);
}