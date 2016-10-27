//===-- EduTLS/src/tls/api/TLSServer.cpp                  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the TLS Server class implementation.
///
//===----------------------------------------------------------------------===//

#include "./TLSServer.h"
#include "../enums/ConnectionStates.h"
#include "../states/TLSConfiguration.h"
#include "../states/TLSSession.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cstring>
#include <iostream>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

TLSServer::TLSServer(TLSConfiguration *config) {
  this->state = new TLSSession(ConnectionEnd_e::server);
  this->config = config;

  this->socket = -1;
  this->pq = NULL;
}

TLSServer::~TLSServer() {
  delete this->state;
  if (this->pq != NULL) {
    delete this->pq;
  }
}

void TLSServer::Handshake() {
  // Begin handshake
  uint8_t buffer[65536];
  this->pq->ReadPacket(buffer);
  return;
}

void TLSServer::AcceptClient(int client) {
  this->socket = client;
  this->pq = new PacketQueue(client, 3, 2);
}
