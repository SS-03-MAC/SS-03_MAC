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
  this->compression_algorithm = CompressionMethod_e::null;

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

  this->mac_key = NULL;
  this->cipher_key = NULL;
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

  if (this->mac_key != NULL) {
    for (i = 0; i < this->mac_key_length; i++) {
      this->mac_key[i] = 0x00;
    }
    free(this->mac_key);
  }

  if (this->cipher_key != NULL) {
    for (i = 0; i < this->enc_key_length; i++) {
      this->cipher_key[i] = 0x00;
    }
    free(this->cipher_key);
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

void SecurityParameters::SetCipher(BulkCipherAlgorithm_e algo) {
  this->bulk_cipher_algorithm = algo;

  switch (algo) {
  case BulkCipherAlgorithm_e::aes_128_cbc:
  case BulkCipherAlgorithm_e::aes_256_cbc:
  case BulkCipherAlgorithm_e::des3_ede_cbc:
    this->cipher_type = CipherType_e::block;
    break;
  case BulkCipherAlgorithm_e::rc4_128:
    this->cipher_type = CipherType_e::stream;
    break;
  default:
    break;
  }

  switch (algo) {
  case BulkCipherAlgorithm_e::rc4_128:
  case BulkCipherAlgorithm_e::aes_128_cbc:
    this->enc_key_length = 16;
    break;
  case BulkCipherAlgorithm_e::des3_ede_cbc:
    this->enc_key_length = 24;
    break;
  case BulkCipherAlgorithm_e::aes_256_cbc:
    this->enc_key_length = 32;
    break;
  default:
    break;
  }

  switch (algo) {
  case BulkCipherAlgorithm_e::aes_128_cbc:
  case BulkCipherAlgorithm_e::aes_256_cbc:
    this->fixed_iv_length = 16;
    this->block_length = 16;
    this->record_iv_length = 16;
    break;
  case BulkCipherAlgorithm_e::des3_ede_cbc:
    this->fixed_iv_length = 8;
    this->block_length = 8;
    this->record_iv_length = 8;
    break;
  case BulkCipherAlgorithm_e::rc4_128:
  default:
    this->fixed_iv_length = 0;
    this->block_length = 0;
    this->record_iv_length = 0;
    break;
    break;
  }
}

void SecurityParameters::SetMAC(MACAlgorithm_e algo) {
  this->mac_algorithm = algo;

  switch (algo) {
  case MACAlgorithm_e::hmac_md5:
    this->mac_length = 16;
    this->mac_key_length = 16;
    break;
  case MACAlgorithm_e::hmac_sha1:
    this->mac_length = 20;
    this->mac_key_length = 20;
    break;
  case MACAlgorithm_e::hmac_sha256:
    this->mac_length = 32;
    this->mac_key_length = 32;
    break;
  default:
    this->mac_length = 0;
    this->mac_key_length = 0;
    break;
  }
}
