//===-- EduTLS/src/tls/messages/HandshakeType.cpp         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Handshake Type protocol.
///
//===----------------------------------------------------------------------===//

#include "Handshake.h"
#include "../enums/HandshakeType.h"
#include "Certificate.h"
#include "CertificateRequest.h"
#include "ClientHello.h"
#include "ClientKeyExchange.h"
#include "Finished.h"
#include "ServerHello.h"
#include "ServerHelloDone.h"
#include "ServerKeyExchange.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

HandshakeType::HandshakeType() { this->body = NULL; }
HandshakeType::HandshakeType(HandshakeContents_t *body) {
  this->body = body;
  this->length = this->body->encode_length();
}
HandshakeType::~HandshakeType() {
  if (this->body != NULL) {
    // delete this->body;
  }
}

int HandshakeType::encode(uint8_t *result) {
  result[0] = static_cast<uint8_t>(this->type);
  result[1] = (this->length >> 16) & 0xFF;
  result[2] = (this->length >> 8) & 0xFF;
  result[3] = this->length & 0xFF;

  return this->body->encode(&(result[4]));
}

size_t HandshakeType::encode_length() { return 4 + this->length; }

int HandshakeType::decode(uint8_t *encoded, size_t length) {
  this->type = static_cast<HandshakeType_e>(encoded[0]);
  this->length = (encoded[1] << 16) | (encoded[2] << 8) | encoded[3];

  switch (this->type) {
  case HandshakeType_e::hello_request:
    break;
  case HandshakeType_e::client_hello:
    this->body = new ClientHello();
    break;
  case HandshakeType_e::server_hello:
    this->body = new ServerHello();
    break;
  case HandshakeType_e::certificate:
    this->body = new Certificate();
    break;
  case HandshakeType_e::server_key_exchange:
    this->body = new ServerKeyExchange();
    break;
  case HandshakeType_e::client_key_exchange:
    this->body = new ClientKeyExchange();
    break;
  case HandshakeType_e::certificate_request:
    this->body = new CertificateRequest();
    break;
  case HandshakeType_e::server_hello_done:
    this->body = new ServerHelloDone();
    break;
  case HandshakeType_e::finished:
    this->body = new Finished();
    break;
  default:
    printf("Unknown handshake message type (%d)!\n", encoded[0]);
    return 1;
    break;
  }

  return this->body->decode(&(encoded[4]), length - 4);
}
