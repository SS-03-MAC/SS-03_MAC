//===-- eHTTP/network/TcpServer.h -------------------------------*- C++ -*-===//
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

#pragma once
namespace network {
/// Starts listening for TCP requests.
/// \returns a file descriptor of the socket.
int tcp_start(uint16_t port);

/// Accepts one client.  Blocks if no clients are available yet.
/// \returns the file descriptor of the accepted socket.
int tcp_accept(int sockfd);
/// Reads everything from \p inStream until EOF and writes it to \p netStreamFd.
int write_stream(int netStreamFd, std::istream &inStream);
}
