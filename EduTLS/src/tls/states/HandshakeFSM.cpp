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
#include "../containers/GenericStreamCipher.h"
#include "../containers/TLSCiphertext.h"
#include "../containers/TLSCompressed.h"
#include "../containers/TLSPlaintext.h"
#include "../enums/ContentType.h"
#include "../messages/ClientHello.h"
#include "../messages/Handshake.h"
#include "../messages/ServerHello.h"
#include "./TLSConfiguration.h"
#include "./TLSSession.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

HandshakeFSM::HandshakeFSM(TLSSession *state, TLSConfiguration *config) {
  this->state = state;
  this->config = config;

  this->current_state = 0;
}

void HandshakeFSM::InitialHandshake(PacketQueue *pq) {
  uint8_t buffer[65536];
  size_t length = pq->ReadPacket(buffer);

  this->pq = pq;

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

  printf("Received client hello! %d\n", m->random.gmt_unix_time);
  CipherSuite *ClientCipherSuites = CipherSuite::FromUint8(m->cipher_suites, m->cipher_suites_lengths);

  this->common = CipherSuite(0, 0);
  bool found = false;
  for (size_t i = 0; i < m->cipher_suites_lengths / 2 && !found; i++) {
    for (size_t j = 0; j < this->config->SupportedCipherSuitesLength && !found; j++) {
      if (ClientCipherSuites[i].Equals(this->config->SupportedCipherSuites[j])) {
        this->common = ClientCipherSuites[i];
        found = true;
        break;
      }
    }
  }

  if (!found) {
    std::cout << "No common cipher suites!" << std::endl;
    return;
  }

  if (this->config->debug) {
    std::cout << "Common cipher suite: " << this->common.String() << std::endl;
  }

  this->current_state = 1;
  this->state->pending_read_params->bulk_cipher_algorithm = this->common.BulkCipherAlgorithm();
  this->state->pending_read_params->mac_algorithm = this->common.MACAlgorithm();
  this->state->pending_write_params->bulk_cipher_algorithm = this->common.BulkCipherAlgorithm();
  this->state->pending_write_params->mac_algorithm = this->common.MACAlgorithm();

  this->ProcessServerHello();
}

void HandshakeFSM::ProcessServerHello() {
  if (this->current_state != 1) {
    return;
  }

  this->state->pending_write_params->GenerateRandom();
  for (size_t i = 0; i < 32; i++) {
    this->state->pending_read_params->server_random[i] = this->state->pending_write_params->server_random[i];
  }

  ServerHello *hello = new ServerHello();
  hello->server_version.major = 0x03;
  hello->server_version.minor = 0x03;
  hello->random.gmt_unix_time = (this->state->pending_write_params->server_random[0] << 24) |
                                    (this->state->pending_write_params->server_random[1] << 16) |
                                    (this->state->pending_write_params->server_random[2] << 8) ||
                                this->state->pending_write_params->server_random[3];

  for (size_t i = 0; i < 28; i++) {
    hello->random.random_bytes[i] = this->state->pending_write_params->server_random[4 + i];
  }
  hello->compression_method = this->state->pending_write_params->compression_algorithm;
  hello->extensions_length = 0;

  HandshakeType *handshake = new HandshakeType(hello);

  uint8_t data[65536];
  size_t length = handshake->encode(data);
  TLSPlaintext *p = new TLSPlaintext(length, data);
  TLSCompressed *c = new TLSCompressed(this->state, p);
  GenericStreamCipher *gcs = new GenericStreamCipher(this->state, c);
  TLSCiphertext *m = new TLSCiphertext(this->state, gcs);

  length = m->encode(data);

  this->pq->WritePacket(data, length);

  delete handshake;

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
