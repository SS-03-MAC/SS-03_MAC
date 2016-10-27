//===-- EduTLS/src/tls/states/SecurityParameters.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the Security Parameters protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ConnectionStates.h"
#include <cstdint>
#include <cstdlib>

class SecurityParameters {
public:
  ConnectionEnd_e entity;
  PRFAlgorithm_e prf_algorithm;
  BulkCipherAlgorithm_e bulk_cipher_algorithm;
  CipherType_e cipher_type;

  uint8_t enc_key_length;
  uint8_t block_length;
  uint8_t fixed_iv_length;
  uint8_t record_iv_length;

  MACAlgorithm_e mac_algorithm;

  uint8_t mac_length;
  uint8_t mac_key_length;

  CompressionMethod_e compression_algorithm;

  uint8_t master_secret[48];
  uint8_t client_random[32];
  uint8_t server_random[32];

  SecurityParameters();
  ~SecurityParameters();

  void GenerateRandom();
};
