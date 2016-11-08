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
#include "../../crypto/crypto.h"
#include "../../encoding/encoding.h"
#include "../abstractions/SendingFactory.h"
#include "../containers/GenericStreamCipher.h"
#include "../containers/TLSCiphertext.h"
#include "../enums/ConnectionStates.h"
#include "../states/HandshakeFSM.h"
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
  this->hs = NULL;
}

TLSServer::~TLSServer() {
  delete this->state;
  if (this->pq != NULL) {
    delete this->pq;
  }
  if (this->hs != NULL) {
    delete this->hs;
  }
}

void TLSServer::Handshake() {
  if (this->hs == NULL) {
    this->hs = new HandshakeFSM(this->state, this->config);
  }

  this->hs->InitialHandshake(this->pq);

  return;
}

void TLSServer::AcceptClient(int client) {
  this->socket = client;
  this->pq = new PacketQueue(client, 3, 2);
}

size_t TLSServer::Read(uint8_t *output) {
  uint8_t buffer[65536];
  size_t length = pq->ReadPacket(buffer);

  bool found_application_packet = false;

  while (!found_application_packet) {
    TLSCiphertext *c = new TLSCiphertext(this->state);

    char hex[2 * length + 1];
    toHex(hex, buffer, length);
    hex[2 * length] = '\0';
    std::cout << "Decoding message:\n" << hex << std::endl;

    c->decode(buffer, length);
    if (c->fragment == NULL) {
      printf("Unknown decoding error (1).");
      return 0;
    }
    if (c->fragment->contents == NULL) {
      printf("Unknown decoding error (2).");
      return 0;
    }
    if (c->fragment->contents->contents == NULL) {
      printf("Unknown decoding error (3).");
      return 0;
    }

    TLSPlaintext *p = c->fragment->contents->contents;
    if (c->type == ContentType_e::application_data) {
      for (size_t i = 0; i < p->length; i++) {
        output[i] = p->fragment[i];
      }

      found_application_packet = true;

      return p->length;
    } else {
      if (this->hs == NULL) {
        this->hs = new HandshakeFSM(this->state, this->config);
      }
      this->hs->ProcessMessage(buffer, length);

      length = pq->ReadPacket(buffer);
    }
  }

  return 0;
}

void TLSServer::Write(uint8_t *data, size_t length) {
  uint8_t buffer[65536];
  size_t buffer_length = 0;

  TLSCiphertext *m = Sending_f::Construct(ContentType_e::handshake, data, length, this->state);

  m->encode(buffer);
  buffer_length = m->encode_length();

  this->pq->WritePacket(buffer, buffer_length);
}

void TLSServer::Close() {}
