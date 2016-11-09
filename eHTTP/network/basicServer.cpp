//
// Created by JoelM on 2016-10-03.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
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
  int f = fork();
  if (f == 0) {
    char buf[10240];
    int cgiPipes[3];
    char *argv[] = {(char *) "echo", (char *) "<h1>Hello from <b>\"CGI\"</b></h1>", NULL};
    ssize_t r;
    // tcp in
    r = read(clientFd, buf, sizeof(buf));
    buf[r] = '\0';
    std::cout << buf << std::endl;

    // cgi out
    pexec("echo", cgiPipes, argv, environ);
    // cgi in
    r = read(cgiPipes[0], buf, sizeof(buf) - 1);
    buf[r] = '\0';

    // tcp out
    char const *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    write(clientFd, header, strlen(header));
    write(clientFd, buf, strlen(buf));
    shutdown(clientFd, SHUT_RDWR);
    exit(0);
  }
}