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
#include "../../EduTLS/src/tls/api/TLSServer.h"
namespace network {
/// Starts listening for TCP requests.
/// \returns a file descriptor of the socket.
int tcp_start(uint16_t port);

/// Accepts one client.  Blocks if no clients are available yet.
/// \returns the file descriptor of the accepted socket.
int tcp_accept(int sockfd);
/// Reads everything from \p inStream until EOF and writes it to \p netStreamFd.
/// \returns the number of bytes transmitted. (overflows are not caught.)
long long write_stream(int netStreamFd, std::istream &inStream);
long long write_stream_tls(TLSServer &client, std::istream &inStream);
/// Reads \p requestContentLen from \p tcpIstream and writes it to \p cgiStdin.  Then reads from \p cgiStdout in
/// \p bufSize chunks and writes them to \p clientFd.
/// \param tcpIstream is the input from the TCP client.
/// \param clientFd is the file descriptor of the TCP client. Used for writing to the client.
/// \param cgiStdout is the stdout file descriptor from the CGI process.
/// \param cgiStdin is the stdin file descriptor for the CGI process.
/// \returns the number of bytes transferred from the CGI script to the TCP client. (Overflows are not caught.)
long long passData(std::istream &tcpIstream,
                   int *clientFd,
                   int cgiStdout,
                   int cgiStdin,
                   size_t requestContentLen,
                   size_t bufSize);
long long passDataTls(std::istream &tcpIstream,
                      TLSServer *client,
                      int cgiStdout,
                      int cgiStdin,
                      size_t requestContentLen,
                      size_t bufSize);
}
