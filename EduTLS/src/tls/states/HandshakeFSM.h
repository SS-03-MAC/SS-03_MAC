//===-- EduTLS/src/tls/states/HandshakeFSM.h              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the Handshake FSM protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../abstractions/PacketQueue.h"
#include "../messages/ClientHello.h"
#include "./TLSConfiguration.h"
#include "./TLSSession.h"
#include <cstdint>
#include <cstdlib>

class HandshakeFSM {
private:
  TLSSession *state;
  TLSConfiguration *config;
  CipherSuite common;

  PacketQueue *pq;

  int current_state;

  void ProcessClientHello(ClientHello *m);
  void ProcessServerHello();
  void ProcessServerCertificate();
  void ProcessServerHelloDone();
  void ProcessClientKeyExchange(uint8_t *data, size_t length);
  void ProcessClientChangeCipherSpec(uint8_t *data, size_t length);
  void ProcessClientFinished(uint8_t *data, size_t length);
  void ProcessServerChangeCipherSpec();
  void ProcessServerFinished();

public:
  HandshakeFSM(TLSSession *state, TLSConfiguration *config);

  void ProcessMessage(uint8_t *data, size_t length);
  void InitialHandshake(PacketQueue *pq);
};
