//===-- EduTLS/src/tls/containers/GenericBlockCipher.cpp  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the Generic Block Cipher
/// protocol.
///
//===----------------------------------------------------------------------===//

#include "./GenericBlockCipher.h"
#include "../../crypto/crypto.h"
#include "../abstractions/HMACFactory.h"
#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

GenericBlockCipher::GenericBlockCipher(TLSSession *state) {
  this->state = state;
  this->iv_length = this->state->current_read_params->record_iv_length;
  this->mac_length = this->state->current_read_params->mac_length;

  this->iv = NULL;
  this->content = NULL;
  this->contents = NULL;
  this->mac = NULL;
  this->padding = NULL;
}

GenericBlockCipher::GenericBlockCipher(TLSSession *state, TLSCompressed *contents) {
  this->state = state;
  this->iv_length = this->state->current_read_params->record_iv_length;
  this->mac_length = this->state->current_read_params->mac_length;

  this->iv = NULL;
  this->content = NULL;
  this->mac = NULL;
  this->padding = NULL;

  this->contents = contents;
  this->content_length = this->contents->encode_length();
  this->content = (uint8_t *)malloc(sizeof(uint8_t) * this->contents->encode_length());
  this->contents->encode(this->content);

  size_t contents_size = this->content_length + this->mac_length;
  this->padding_length = this->iv_length - (contents_size % this->iv_length) - 1;
  this->padding = (uint8_t *)malloc(sizeof(uint8_t) * this->padding_length);
  for (size_t i = 0; i < this->padding_length; i++) {
    this->padding[i] = this->padding_length;
  }
}

GenericBlockCipher::~GenericBlockCipher() {
  if (this->iv != NULL) {
    free(this->iv);
  }
  if (this->content != NULL) {
    free(this->content);
  }
  if (this->mac != NULL) {
    free(this->mac);
  }
  if (this->padding != NULL) {
    free(this->padding);
  }
}

int GenericBlockCipher::encode(uint8_t *result) {
  this->iv = (uint8_t *)malloc(sizeof(uint8_t) * this->iv_length);

  edutls_rand_bytes(this->iv, this->iv_length);

  size_t i = 0;

  hmac *h =
      HMAC_f::Construct(this->state->current_write_params->mac_algorithm, this->state->current_write_params->mac_key,
                        this->state->current_write_params->mac_key_length);

  this->mac = (uint8_t *)malloc(sizeof(uint8_t) * this->mac_length);

  uint8_t raw_data[13 + this->content_length];
  raw_data[0] = (this->state->current_write_params->sequence_number >> 56) & 0xFF;
  raw_data[1] = (this->state->current_write_params->sequence_number >> 48) & 0xFF;
  raw_data[2] = (this->state->current_write_params->sequence_number >> 40) & 0xFF;
  raw_data[3] = (this->state->current_write_params->sequence_number >> 32) & 0xFF;
  raw_data[4] = (this->state->current_write_params->sequence_number >> 24) & 0xFF;
  raw_data[5] = (this->state->current_write_params->sequence_number >> 16) & 0xFF;
  raw_data[6] = (this->state->current_write_params->sequence_number >> 8) & 0xFF;
  raw_data[7] = (this->state->current_write_params->sequence_number >> 0) & 0xFF;

  raw_data[8] = static_cast<uint8_t>(this->type);
  raw_data[9] = this->version.major;
  raw_data[10] = this->version.minor;
  raw_data[11] = (this->content_length >> 8) & 0xFF;
  raw_data[12] = this->content_length & 0xFF;
  for (i = 0; i < this->content_length; i++) {
    raw_data[13 + i] = this->content[i];
  }
  for (i = 0; i < this->content_length + 13; i++) {
  }

  h->sum(this->mac, raw_data, this->content_length + 13);
  this->state->current_write_params->sequence_number += 1;

  delete h;

  uint8_t ciphertext[this->iv_length + this->content_length + this->mac_length + this->padding_length + 1];
  uint8_t plaintext[this->content_length + this->mac_length + this->padding_length + 1];

  size_t p_p = 0;
  i = 0;
  for (i = 0; i < this->content_length; i++) {
    plaintext[p_p++] = this->content[i];
  }
  for (i = 0; i < this->mac_length; i++) {
    plaintext[p_p++] = this->mac[i];
  }
  for (i = 0; i < this->padding_length; i++) {
    plaintext[p_p++] = this->padding[i];
  }
  plaintext[p_p++] = this->padding_length;

  aes *cipher =
      new aes(this->state->current_write_params->cipher_key, this->state->current_write_params->enc_key_length);
  cbc *block_mode = new cbc(cipher, this->iv);
  block_mode->encrypt(&(ciphertext[this->iv_length]), plaintext,
                      this->content_length + this->mac_length + this->padding_length + 1);

  for (i = 0; i < this->iv_length; i++) {
    ciphertext[i] = this->iv[i];
  }

  for (i = 0; i < this->iv_length + this->content_length + this->mac_length + this->padding_length + 1; i++) {
    result[i] = ciphertext[i];
  }

  return 0;
}

size_t GenericBlockCipher::encode_length() {
  return this->iv_length + this->content_length + this->mac_length + this->padding_length + 1;
}

int GenericBlockCipher::decode(uint8_t *encoded, size_t length) {
  bool valid_padding = true;
  bool valid_mac = false;

  this->iv = (uint8_t *)malloc(sizeof(uint8_t) * this->iv_length);
  size_t i = 0;
  for (i = 0; i < this->iv_length; i++) {
    iv[i] = encoded[i];
  }

  size_t data_length = length - this->iv_length;
  uint8_t data[data_length];
  for (i = 0; i < data_length; i++) {
    data[i] = 0x00;
  }

  aes *cipher = new aes(this->state->current_read_params->cipher_key, this->state->current_read_params->enc_key_length);
  cbc *block_mode = new cbc(cipher, this->iv);
  block_mode->decrypt(data, &(encoded[this->iv_length]), data_length);

  i = 0;

  this->padding_length = data[data_length - 1];
  this->padding = (uint8_t *)malloc(sizeof(uint8_t) * padding_length);
  for (i = 0; i < padding_length; i++) {
    this->padding[i] = data[data_length - 2 - i];
    valid_padding = valid_padding && (this->padding[i] == this->padding_length);
  }

  this->mac = (uint8_t *)malloc(sizeof(uint8_t) * this->mac_length);
  size_t data_mac_end = data_length - padding_length - 1;
  size_t o_p = 0;
  for (i = data_mac_end - this->mac_length; i < data_mac_end; i++) {
    this->mac[o_p] = data[i];
    o_p += 1;
  }

  size_t data_finish = data_mac_end - mac_length;
  o_p = 0;
  this->content_length = data_finish;
  this->content = (uint8_t *)malloc(sizeof(uint8_t) * data_finish);
  for (i = 0; i < data_finish; i++) {
    this->content[i] = data[i];
  }

  hmac *h =
      HMAC_f::Construct(this->state->current_read_params->mac_algorithm, this->state->current_read_params->mac_key,
                        this->state->current_read_params->mac_key_length);

  if (h == NULL) {
    valid_mac = true;
  } else {
    uint8_t calculated_mac[this->mac_length] = {0x00, 0x00, 0x00};

    uint8_t raw_data[13 + this->content_length];
    raw_data[0] = (this->state->current_read_params->sequence_number >> 56) & 0xFF;
    raw_data[1] = (this->state->current_read_params->sequence_number >> 48) & 0xFF;
    raw_data[2] = (this->state->current_read_params->sequence_number >> 40) & 0xFF;
    raw_data[3] = (this->state->current_read_params->sequence_number >> 32) & 0xFF;
    raw_data[4] = (this->state->current_read_params->sequence_number >> 24) & 0xFF;
    raw_data[5] = (this->state->current_read_params->sequence_number >> 16) & 0xFF;
    raw_data[6] = (this->state->current_read_params->sequence_number >> 8) & 0xFF;
    raw_data[7] = (this->state->current_read_params->sequence_number >> 0) & 0xFF;
    raw_data[8] = static_cast<uint8_t>(this->type);
    raw_data[9] = this->version.major;
    raw_data[10] = this->version.minor;
    raw_data[11] = (this->content_length >> 8) & 0xFF;
    raw_data[12] = this->content_length & 0xFF;
    for (i = 0; i < this->content_length; i++) {
      raw_data[13 + i] = this->content[i];
    }

    h->sum(calculated_mac, raw_data, this->content_length + 13);
    this->state->current_read_params->sequence_number += 1;

    valid_mac = true;
    for (i = 0; i < this->mac_length; i++) {
      valid_mac = valid_mac && (this->mac[i] == calculated_mac[i]);
    }

    delete h;
  }

  if (valid_mac == false || valid_padding == false) {
    this->contents = NULL;
    return 1;
  }

  this->contents = new TLSCompressed(this->state);

  this->contents->decode(this->content, this->content_length);

  return 0;
}
