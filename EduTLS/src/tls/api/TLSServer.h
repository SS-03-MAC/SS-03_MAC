//===-- EduTLS/src/tls/api/TLSServer.h                    -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the TLS Server class declaration.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../abstractions/PacketQueue.h"
#include "../states/TLSConfiguration.h"
#include "../states/TLSSession.h"

#include <cstdint>
#include <ctime>

class TLSServer {
private:
  TLSSession *state;
  TLSConfiguration *config;

  int socket;

  time_t last_packet;

  PacketQueue *pq;

public:
  TLSServer(TLSConfiguration *config);
  ~TLSServer();

  void Handshake();
  void AcceptClient(int client);
};
