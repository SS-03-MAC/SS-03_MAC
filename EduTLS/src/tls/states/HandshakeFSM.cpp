//===-- EduTLS/src/tls/states/HandshakeFSM.cpp            -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state implementation for the Handshake FSM protocol.
///
//===----------------------------------------------------------------------===//

#include "./HandshakeFSM.h"
#include "../abstractions/PacketQueue.h"
#include "../containers/TLSCiphertext.h"
#include "../containers/TLSCompressed.h"
#include "../containers/TLSPlaintext.h"
#include "../enums/ContentType.h"
#include "../messages/ClientHello.h"
#include "../messages/Handshake.h"
#include "./TLSSession.h"
#include <cstdint>
#include <cstdlib>

HandshakeFSM::HandshakeFSM(TLSSession *state) {
  this->state = state;
  this->current_state = 0;
}

void HandshakeFSM::InitialHandshake(PacketQueue *pq) {
  uint8_t buffer[65536];
  size_t length = pq->ReadPacket(buffer);

  this->ProcessMessage(buffer, length);
}

void HandshakeFSM::ProcessMessage(uint8_t *data, size_t length) {
  TLSCiphertext *c = new TLSCiphertext(this->state);
  c->decode(data, length);
  TLSPlaintext *p = c->fragment->contents->contents;

  if (c->type == ContentType_e::handshake) {
    HandshakeType *h = new HandshakeType();
    h->decode(p->fragment, p->length);

    switch (h->type) {
    case HandshakeType_e::client_hello:
      ProcessClientHello(dynamic_cast<ClientHello *>(h->body));
      break;
    default:
      break;
    }

    delete h;
  } else if (c->type == ContentType_e::change_cipher_spec) {
  }

  delete c;
}

void HandshakeFSM::ProcessClientHello(ClientHello *m) {
  if (this->current_state != 0) {
    return;
  }

  this->current_state = 1;

  printf("Received client hello! %d\n", m->random.gmt_unix_time);
  this->ProcessServerHello();
}

void HandshakeFSM::ProcessServerHello() {
  if (this->current_state != 1) {
    return;
  }
  this->current_state = 2;
  this->ProcessServerCertificate();
}

void HandshakeFSM::ProcessServerCertificate() {
  if (this->current_state != 2) {
    return;
  }

  this->current_state = 3;
  this->ProcessServerHelloDone();
}

void HandshakeFSM::ProcessServerHelloDone() {
  if (this->current_state != 3) {
    return;
  }
  this->current_state = 4;
}

void HandshakeFSM::ProcessClientKeyExchange(uint8_t *, size_t) {}
void HandshakeFSM::ProcessClientChangeCipherSpec(uint8_t *, size_t) {}
void HandshakeFSM::ProcessClientFinished(uint8_t *, size_t) {}
void HandshakeFSM::ProcessServerChangeCipherSpec() {}
void HandshakeFSM::ProcessServerFinished() {}
