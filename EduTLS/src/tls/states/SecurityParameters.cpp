//===-- EduTLS/src/tls/states/SecurityParameters.cpp      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state implementations for the Security Parameters protocol.
///
//===----------------------------------------------------------------------===//

#include "SecurityParameters.h"
#include "../../crypto/entropy.h"
#include "../enums/ConnectionStates.h"
#include <cstdint>
#include <cstdlib>

SecurityParameters::SecurityParameters() {
  size_t i = 0;

  this->prf_algorithm = PRFAlgorithm_e::tls_prf_sha256;
  this->bulk_cipher_algorithm = BulkCipherAlgorithm_e::null;
  this->cipher_type = CipherType_e::stream;
  this->mac_algorithm = MACAlgorithm_e::null;

  this->enc_key_length = 0;
  this->block_length = 0;
  this->fixed_iv_length = 0;
  this->record_iv_length = 0;
  this->mac_length = 0;
  this->mac_key_length = 0;

  for (i = 0; i < 32; i++) {
    server_random[i] = 0x00;
    client_random[i] = 0x00;
  }
  for (i = 0; i < 48; i++) {
    master_secret[i] = 0x00;
  }
}

SecurityParameters::~SecurityParameters() {
  size_t i = 0;
  for (i = 0; i < 32; i++) {
    server_random[i] = 0x00;
    client_random[i] = 0x00;
  }
  for (i = 0; i < 48; i++) {
    master_secret[i] = 0x00;
  }
}

void SecurityParameters::GenerateRandom() {
  switch (this->entity) {
  case ConnectionEnd_e::server:
    edutls_rand_bytes(this->server_random, 32);
    break;
  case ConnectionEnd_e::client:
    edutls_rand_bytes(this->client_random, 32);
    break;
  }
}
