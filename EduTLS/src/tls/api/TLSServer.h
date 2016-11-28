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
#include "../states/HandshakeFSM.h"
#include "../states/TLSConfiguration.h"
#include "../states/TLSSession.h"

#include <cstdint>
#include <ctime>

class TLSServer {
private:
  TLSSession *state;
  TLSConfiguration *config;

  HandshakeFSM *hs;

  int socket;

  PacketQueue *pq;

  bool closed;

public:
  TLSServer(TLSConfiguration *config);
  ~TLSServer();

  void Handshake();
  void AcceptClient(int client);

  bool IsClosed() { return this->closed; }

  size_t Read(uint8_t *output);
  void Write(uint8_t *data, size_t length);
  void Close();
};
