//===-- EduTLS/src/tls/messages/ClientKeyExchange.cpp     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Client Key Exchange protocol.
///
//===----------------------------------------------------------------------===//

#include "ClientKeyExchange.h"
#include "../../crypto/crypto.h"
#include "../../encoding/encoding.h"
#include "../states/TLSConfiguration.h"
#include "../states/TLSSession.h"
#include "ProtocolVersion.h"
#include <cstdint>
#include <gmp.h>

ClientKeyExchange::ClientKeyExchange() {
  this->length = 0;
  this->encrypted = NULL;
}
ClientKeyExchange::~ClientKeyExchange() {
  if (this->encrypted != NULL) {
    free(this->encrypted);
  }
}

int ClientKeyExchange::encrypt(TLSSession *, TLSConfiguration *) { return 0; }

int ClientKeyExchange::decrypt(TLSSession *state, TLSConfiguration *config) {
  if (this->encrypted == NULL) {
    return 3;
  }
  mpz_t output;
  mpz_init(output);
  mpz_t input;
  mpz_init(input);
  mpz_import(input, this->length, 1, sizeof(uint8_t), 0, 0, this->encrypted);

  uint8_t R[48];
  edutls_rand_bytes(R, 48);
  config->key.decrypt(output, input);

  size_t raw_length;
  uint8_t *raw_data = NULL;
  mpz_export(NULL, &raw_length, 1, sizeof(uint8_t), 0, 0, output);
  raw_data = (uint8_t *)malloc(sizeof(uint8_t) * raw_length + 1);
  mpz_export(&(raw_data[1]), &raw_length, 1, sizeof(uint8_t), 0, 0, output);
  raw_data[0] = 0x00;
  raw_length += 1;

  size_t actual_length = edutls_unpad_pkcs1_length(raw_data, raw_length);
  uint8_t *actual_data = (uint8_t *)malloc(sizeof(uint8_t) * actual_length);
  bool padding = edutls_unpad_pkcs1(actual_data, raw_data, raw_length);

  size_t i = 0;
  if (padding == false || actual_length != 48) {
    this->client_version.major = R[0];
    this->client_version.minor = R[1];
    for (i = 0; i < 46; i++) {
      this->random[i] = R[i + 2];
    }
    return 1;
  } else if (actual_data[0] != state->pending_read_params->client_version.major ||
             actual_data[1] != state->pending_read_params->client_version.minor) {
    this->client_version.major = R[0];
    this->client_version.minor = R[1];
    for (i = 0; i < 46; i++) {
      this->random[i] = R[i + 2];
    }
    return 2;
  }

  this->client_version.major = actual_data[0];
  this->client_version.minor = actual_data[1];
  for (i = 0; i < 46; i++) {
    this->random[i] = actual_data[i + 2];
  }

  return 0;
}

int ClientKeyExchange::encode(uint8_t *result) {
  result[0] = (length >> 8) & 0xFF;
  result[1] = length & 0xFF;

  size_t offset = 0;
  for (offset = 0; offset < this->length; offset++) {
    result[2 + offset] = this->encrypted[offset];
  }

  return 0;
}

size_t ClientKeyExchange::encode_length() { return 2 + this->length; }

int ClientKeyExchange::decode(uint8_t *encoded, size_t length) {
  if (length < 2) {
    return 1;
  }
  this->length = (encoded[0] << 8) | encoded[1];

  this->encrypted = (uint8_t *)malloc(sizeof(uint8_t) * this->length);

  size_t offset = 0;
  for (offset = 0; offset < this->length && offset + 2 < length; offset++) {
    this->encrypted[offset] = encoded[2 + offset];
  }

  return 0;
}
