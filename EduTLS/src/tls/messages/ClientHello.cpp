//===-- EduTLS/src/tls/messages/ClientHello.cpp           -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Client Hello protocol.
///
//===----------------------------------------------------------------------===//

#include "ClientHello.h"
#include "Handshake.h"

#include "../enums/CompressionMethod.h"
#include "../enums/HandshakeType.h"
#include "../interfaces/encodable.h"
#include "./Extension.h"
#include "./ProtocolVersion.h"
#include "./Random.h"

#include <cstdint>
#include <cstdlib>

ClientHello::ClientHello() {
  this->session_id = NULL;
  this->cipher_suites = NULL;
  this->compression_methods = NULL;
  this->extensions = NULL;
}
ClientHello::~ClientHello() {
  if (this->session_id != NULL) {
    free(this->session_id);
  }
  if (this->cipher_suites != NULL) {
    free(this->cipher_suites);
  }
  if (this->compression_methods != NULL) {
    free(this->compression_methods);
  }
  if (this->extensions != NULL) {
    free(this->extensions);
  }
}

int ClientHello::encode(uint8_t *result) {
  size_t r_p = 0;
  size_t i = 0;

  result[r_p++] = this->client_version.major;
  result[r_p++] = this->client_version.minor;

  this->random.encode(&(result[r_p]));
  r_p += this->random.encode_length();

  result[r_p++] = this->session_id_length;
  for (i = 0; i < this->session_id_length; i++) {
    result[r_p++] = this->session_id[i];
  }

  result[r_p++] = ((this->cipher_suites_lengths * 2) >> 8) & 0xFF;
  result[r_p++] = (this->cipher_suites_lengths * 2) & 0xFF;
  for (i = 0; i < this->cipher_suites_lengths * 2; i++) {
    result[r_p++] = this->cipher_suites[i];
  }

  result[r_p++] = this->compression_methods_length;
  for (i = 0; i < this->compression_methods_length; i++) {
    result[r_p++] = static_cast<uint8_t>(this->compression_methods[i]);
  }

  uint16_t ext_len = 0;
  for (i = 0; i < this->extensions_length; i++) {
    ext_len += this->extensions[i].encode_length();
  }

  result[r_p++] = (ext_len >> 8) & 0xFF;
  result[r_p++] = ext_len & 0xFF;
  for (i = 0; i < this->extensions_length; i++) {
    this->extensions[i].encode(&(result[r_p]));
    r_p += this->extensions[i].encode_length();
  }

  return 0;
}

size_t ClientHello::encode_length() {
  uint16_t ext_len = 0;
  size_t i = 0;
  for (i = 0; i < this->extensions_length; i++) {
    ext_len += this->extensions[i].encode_length();
  }

  return 2 + this->random.encode_length() + 1 + this->session_id_length + 2 + (this->cipher_suites_lengths * 2) + 1 +
         this->compression_methods_length + 2 + ext_len;
}

int ClientHello::decode(uint8_t *encoded, size_t length) {
  size_t r_p = 0;
  size_t i = 0;
  this->client_version.major = encoded[r_p++];
  this->client_version.minor = encoded[r_p++];

  this->random.decode(&(encoded[r_p]), 32);
  r_p += 32;

  this->session_id_length = encoded[r_p++];

  this->session_id = (uint8_t *)malloc(sizeof(uint8_t) * this->session_id_length);

  for (i = 0; i < this->session_id_length && r_p < length; i++) {
    this->session_id[i] = encoded[r_p++];
  }

  this->cipher_suites_lengths = (encoded[r_p] << 8) | encoded[r_p + 1];
  r_p += 2;
  this->cipher_suites = (uint8_t *)malloc(sizeof(uint8_t) * this->cipher_suites_lengths);
  for (i = 0; i < this->cipher_suites_lengths && r_p < length; i++) {
    this->cipher_suites[i] = encoded[r_p++];
  }
  this->cipher_suites_lengths = this->cipher_suites_lengths / 2;

  this->compression_methods_length = encoded[r_p++];
  this->compression_methods =
      (CompressionMethod_e *)malloc(sizeof(CompressionMethod_e) * this->compression_methods_length);
  for (i = 0; i < this->compression_methods_length && r_p < length; i++) {
    this->compression_methods[i] = static_cast<CompressionMethod_e>(encoded[r_p++]);
  }

  this->extensions_length = (encoded[r_p] << 8) | encoded[r_p + 1];
  r_p += 2;
  // Ignore extensions for now.

  return 0;
}
