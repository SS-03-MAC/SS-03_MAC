//
// Created by JoelM on 2016-09-27.
//

#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
int main(int argc, char *argv[]) {
  int socks[2];
  int s = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(80);
  addr.sin_family = AF_INET;

  int c = connect(s, (const struct sockaddr *) &addr, sizeof(addr));

  char buf[1024] = "GET / HTTP/1.1\nHost: 127.0.0.1\n\n";
  write(s, buf, strlen(buf));
  ssize_t r = read(s, (void *) buf, sizeof(buf));
  std::cout << "Read " << r << " bytes" << std::endl;
  std::cout << buf << std::endl;
}