//
// Created by JoelM on 2016-09-27.
//

#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
int main(int argc, char *argv[]) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int b = bind(s, (struct sockaddr *) &addr, sizeof(addr));
  int l = listen(s, 1);
  struct sockaddr_in client_addr;
  std::cout << "Waiting for client..." << std::endl;
  socklen_t *clilen = (socklen_t *) sizeof(client_addr);
  int c = accept(s, (sockaddr *) &client_addr, (socklen_t *) &clilen);

  std::cout << "Client connected from " << htonl(client_addr.sin_addr.s_addr) << std::endl;
  char buf[1024];
  ssize_t r = read(c, buf, sizeof(buf) - 1);
  std::cout << "Read " << r << " bytes" << std::endl;
  buf[r] = '\0';
  std::cout << buf << std::endl;
  const char *out = "HTTP/1.1 200 OK\r\n\r\nHello world\r\n";
  write(c, out, strlen(out));
  close(c);
  close(s);
}