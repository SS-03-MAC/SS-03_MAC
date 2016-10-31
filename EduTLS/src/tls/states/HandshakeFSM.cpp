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
#include "../../encoding/hex.h"
#include "../abstractions/PacketQueue.h"
#include "../containers/GenericStreamCipher.h"
#include "../containers/TLSCiphertext.h"
#include "../containers/TLSCompressed.h"
#include "../containers/TLSPlaintext.h"
#include "../enums/ContentType.h"
#include "../messages/Certificate.h"
#include "../messages/ClientHello.h"
#include "../messages/ClientKeyExchange.h"
#include "../messages/Handshake.h"
#include "../messages/ServerHello.h"
#include "../messages/ServerHelloDone.h"
#include "./TLSConfiguration.h"
#include "./TLSSession.h"
#include "SecurityParameters.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>

HandshakeFSM::HandshakeFSM(TLSSession *state, TLSConfiguration *config) {
  this->state = state;
  this->config = config;

  this->current_state = 0;
}

void HandshakeFSM::InitialHandshake(PacketQueue *pq) {
  this->pq = pq;

  // Once for ClientHello
  uint8_t buffer[65536];
  size_t length = pq->ReadPacket(buffer);
  this->ProcessMessage(buffer, length);

  // Once for ClientKeyExchange
  length = pq->ReadPacket(buffer);
  this->ProcessMessage(buffer, length);

  // Once for ChangeCipherSpec
  length = pq->ReadPacket(buffer);
  this->ProcessMessage(buffer, length);

  // Once for Finished
  length = pq->ReadPacket(buffer);
  this->ProcessMessage(buffer, length);
}

void HandshakeFSM::ProcessMessage(uint8_t *data, size_t length) {
  TLSCiphertext *c = new TLSCiphertext(this->state);

  char hex[2 * length + 1];
  toHex(hex, data, length);
  hex[2 * length] = '\0';
  std::cout << "Decoding message:\n" << hex << std::endl;

  c->decode(data, length);
  if (c->fragment == NULL || c->fragment->contents == NULL || c->fragment->contents->contents == NULL) {
    printf("Unknown decoding error.");
    return;
  }
  TLSPlaintext *p = c->fragment->contents->contents;

  if (c->type == ContentType_e::handshake) {
    HandshakeType *h = new HandshakeType();

    h->decode(p->fragment, p->length);

    switch (h->type) {
    case HandshakeType_e::client_hello:
      ProcessClientHello(dynamic_cast<ClientHello *>(h->body));
      break;
    case HandshakeType_e::client_key_exchange:
      ProcessClientKeyExchange(dynamic_cast<ClientKeyExchange *>(h->body));
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

  // printf("Received client hello! %d\n", m->random.gmt_unix_time);
  // printf("Cipher suites: %d bytes, %d count\n", 2 * m->cipher_suites_lengths, m->cipher_suites_lengths);
  CipherSuite *ClientCipherSuites = CipherSuite::FromUint8(m->cipher_suites, 2 * m->cipher_suites_lengths);

  this->common = CipherSuite(0, 0);
  bool found = false;
  for (size_t i = 0; i < m->cipher_suites_lengths && !found; i++) {
    for (size_t j = 0; j < this->config->SupportedCipherSuitesLength && !found; j++) {
      if (ClientCipherSuites[i].Equals(this->config->SupportedCipherSuites[j])) {
        this->common = ClientCipherSuites[i];
        found = true;
        break;
      }
    }
  }

  if (!found) {
    std::cout << "No common cipher suites!" << std::endl << "Client Cipher Suites: " << std::endl;
    for (size_t i = 0; i < m->cipher_suites_lengths; i++) {
      std::cout << "\t[" << i << "]: " << ClientCipherSuites[i].String() << std::endl;
    }
    std::cout << "Server Cipher Suites:" << std::endl;
    for (size_t i = 0; i < this->config->SupportedCipherSuitesLength; i++) {
      std::cout << "\t[" << i << "]: " << this->config->SupportedCipherSuites[i].String() << std::endl;
    }

    return;
  }

  if (this->config->debug) {
    std::cout << "Common cipher suite: " << this->common.String() << std::endl;
  }

  this->current_state = 1;
  this->state->pending_read_params = new SecurityParameters();
  this->state->pending_write_params = new SecurityParameters();
  this->state->pending_read_params->entity = this->state->current_read_params->entity;
  this->state->pending_write_params->entity = this->state->current_write_params->entity;
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
  hello->session_id_length = 0;
  hello->cipher_suite[0] = this->common.big;
  hello->cipher_suite[1] = this->common.little;

  HandshakeType *handshake = new HandshakeType(hello);
  handshake->type = HandshakeType_e::server_hello;

  uint8_t data[65536];
  size_t length = handshake->encode_length();
  handshake->encode(data);
  // printf("\nLength of handshake: %zu\n", length);
  TLSPlaintext *p = new TLSPlaintext(length, data);
  // printf("Plaintext length: %d\n", p->length);
  TLSCompressed *c = new TLSCompressed(this->state, p);
  // printf("Compressed length: %d\n", c->length);
  GenericStreamCipher *gcs = new GenericStreamCipher(this->state, c);
  // printf("GCS Length: %d + %d\n", gcs->contents_length, gcs->mac_length);
  TLSCiphertext *m = new TLSCiphertext(this->state, gcs);
  // printf("Ciphertext length: %d\n", m->length);
  m->version.major = hello->server_version.major;
  m->version.minor = hello->server_version.minor;
  m->type = ContentType_e::handshake;

  m->encode(data);
  length = m->encode_length();

  char hex[2 * length + 1];
  toHex(hex, data, length);
  hex[2 * length] = '\0';

  // printf("Sending packet: \n\t%s\n", hex);

  // printf("Length of TLSCiphertext: %zu\n", length);

  this->pq->WritePacket(data, length);

  delete handshake;
  delete hello;
  delete m;

  // printf("Sent server hello.\n");

  this->current_state = 2;
  this->ProcessServerCertificate();
}

void HandshakeFSM::ProcessServerCertificate() {
  if (this->current_state != 2) {
    return;
  }

  Certificate *certs = new Certificate();
  Certificate_t *cert = new Certificate_t();
  size_t i = 0;
  cert->certificate_data = (uint8_t *)malloc(sizeof(uint8_t) * this->config->cert.certificate_length);
  for (i = 0; i < this->config->cert.certificate_length; i++) {
    cert->certificate_data[i] = this->config->cert.certificate_data[i];
  }
  cert->certificate_length = this->config->cert.certificate_length;
  certs->certificates_length = 1;
  certs->certificates = cert;

  HandshakeType *handshake = new HandshakeType(certs);
  handshake->type = HandshakeType_e::certificate;

  uint8_t data[65536];
  size_t length = 0;
  length = handshake->encode_length();
  handshake->encode(data);
  // printf("\nLength of handshake: %zu\n", length);
  TLSPlaintext *p = new TLSPlaintext(length, data);
  // printf("Plaintext length: %d\n", p->length);
  TLSCompressed *c = new TLSCompressed(this->state, p);
  // printf("Compressed length: %d\n", c->length);
  GenericStreamCipher *gcs = new GenericStreamCipher(this->state, c);
  // printf("GCS Length: %d + %d\n", gcs->contents_length, gcs->mac_length);
  TLSCiphertext *m = new TLSCiphertext(this->state, gcs);
  // printf("Ciphertext length: %d\n", m->length);
  m->version.major = 0x03;
  m->version.minor = 0x03;
  m->type = ContentType_e::handshake;

  m->encode(data);
  length = m->encode_length();

  char hex[2 * length + 1];
  toHex(hex, data, length);
  hex[2 * length] = '\0';

  // printf("Sending packet: \n\t%s\n", hex);

  // printf("Length of TLSCiphertext: %zu\n", length);

  this->pq->WritePacket(data, length);

  delete handshake;
  delete m;

  this->current_state = 3;
  this->ProcessServerHelloDone();
}

void HandshakeFSM::ProcessServerHelloDone() {
  if (this->current_state != 3) {
    return;
  }

  ServerHelloDone *done = new ServerHelloDone();

  HandshakeType *handshake = new HandshakeType(done);
  handshake->type = HandshakeType_e::server_hello_done;

  uint8_t data[65536];
  size_t length = 0;
  length = handshake->encode_length();
  handshake->encode(data);
  // printf("\nLength of handshake: %zu\n", length);
  TLSPlaintext *p = new TLSPlaintext(length, data);
  // printf("Plaintext length: %d\n", p->length);
  TLSCompressed *c = new TLSCompressed(this->state, p);
  // printf("Compressed length: %d\n", c->length);
  GenericStreamCipher *gcs = new GenericStreamCipher(this->state, c);
  // printf("GCS Length: %d + %d\n", gcs->contents_length, gcs->mac_length);
  TLSCiphertext *m = new TLSCiphertext(this->state, gcs);
  // printf("Ciphertext length: %d\n", m->length);
  m->version.major = 0x03;
  m->version.minor = 0x03;
  m->type = ContentType_e::handshake;

  m->encode(data);
  length = m->encode_length();

  char hex[2 * length + 1];
  toHex(hex, data, length);
  hex[2 * length] = '\0';

  // printf("Sending packet: \n\t%s\n", hex);

  // printf("Length of TLSCiphertext: %zu\n", length);

  this->pq->WritePacket(data, length);

  delete handshake;
  delete m;

  this->current_state = 4;
}

void HandshakeFSM::ProcessClientKeyExchange(ClientKeyExchange *) {}

void HandshakeFSM::ProcessClientChangeCipherSpec(uint8_t *, size_t) {}
void HandshakeFSM::ProcessClientFinished(uint8_t *, size_t) {}
void HandshakeFSM::ProcessServerChangeCipherSpec() {}
void HandshakeFSM::ProcessServerFinished() {}
