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

#include "../../crypto/crypto.h"
#include "../abstractions/PacketQueue.h"
#include "../messages/ChangeCipherSpec.h"
#include "../messages/ClientHello.h"
#include "../messages/ClientKeyExchange.h"
#include "../messages/Finished.h"
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

  hash *client_finished_hash;
  hash *server_finished_hash;

  int current_state;

  void ProcessClientHello(ClientHello *m);
  void ProcessServerHello();
  void ProcessServerCertificate();
  void ProcessServerHelloDone();
  void ProcessClientKeyExchange(ClientKeyExchange *m);
  void ProcessClientChangeCipherSpec(ChangeCipherSpec *ccs);
  void ProcessClientFinished(Finished *f);
  void ProcessServerChangeCipherSpec();
  void ProcessServerFinished();

public:
  HandshakeFSM(TLSSession *state, TLSConfiguration *config);
  ~HandshakeFSM();

  void ProcessMessage(uint8_t *data, size_t length);
  void InitialHandshake(PacketQueue *pq);
};
