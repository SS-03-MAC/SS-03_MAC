//
// Created by JoelM on 2016-10-03.
//

#pragma once
namespace network {
  int tcp_start(uint16_t port);

  int tcp_accept(int sockfd);
  int write_stream(int netStreamFd, std::istream &inStream);
}
