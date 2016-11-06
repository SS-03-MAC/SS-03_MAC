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
#include "../../crypto/crypto.h"
#include "../../encoding/hex.h"
#include "../abstractions/PacketQueue.h"
#include "../containers/GenericStreamCipher.h"
#include "../containers/TLSCiphertext.h"
#include "../containers/TLSCompressed.h"
#include "../containers/TLSPlaintext.h"
#include "../enums/ContentType.h"
#include "../messages/Certificate.h"
#include "../messages/ChangeCipherSpec.h"
#include "../messages/ClientHello.h"
#include "../messages/ClientKeyExchange.h"
#include "../messages/Finished.h"
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
  this->server_finished_hash = NULL;
  this->client_finished_hash = NULL;
}

HandshakeFSM::~HandshakeFSM() {
  if (this->server_finished_hash != NULL) {
    delete this->server_finished_hash;
  }

  if (this->client_finished_hash != NULL) {
    delete this->client_finished_hash;
  }
}

void HandshakeFSM::InitialHandshake(PacketQueue *pq) {
  this->pq = pq;

  if (this->client_finished_hash == NULL) {
    this->client_finished_hash = new sha2_256();
  }
  if (this->server_finished_hash == NULL) {
    this->server_finished_hash = new sha2_256();
  }
  this->client_finished_hash->init();
  this->server_finished_hash->init();

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
  if (c->fragment == NULL) {
    printf("Unknown decoding error (1).");
    return;
  }
  if (c->fragment->contents == NULL) {
    printf("Unknown decoding error (2).");
    return;
  }
  if (c->fragment->contents->contents == NULL) {
    printf("Unknown decoding error (3).");
    return;
  }

  TLSPlaintext *p = c->fragment->contents->contents;

  if (c->type == ContentType_e::handshake) {
    HandshakeType *h = new HandshakeType();

    printf("Decoding HandshakeType: %d\n", h->decode(p->fragment, p->length));

    switch (h->type) {
    case HandshakeType_e::client_hello:
      this->client_finished_hash->update(p->fragment, p->length);
      this->server_finished_hash->update(p->fragment, p->length);
      printf("Added to SHA256 state...\n");
      this->ProcessClientHello(dynamic_cast<ClientHello *>(h->body));
      break;
    case HandshakeType_e::client_key_exchange:
      this->client_finished_hash->update(p->fragment, p->length);
      this->server_finished_hash->update(p->fragment, p->length);
      printf("Added to SHA256 state...\n");
      this->ProcessClientKeyExchange(dynamic_cast<ClientKeyExchange *>(h->body));
      break;
    case HandshakeType_e::finished:
      this->server_finished_hash->update(p->fragment, p->length);
      printf("Added to Server SHA256 state...\n");
      this->ProcessClientFinished(dynamic_cast<Finished *>(h->body));
      break;
    default:
      printf("Unknown HandshakeType->type: %d\n", static_cast<int>(h->type));
      break;
    }

    delete h;
  } else if (c->type == ContentType_e::change_cipher_spec) {
    ChangeCipherSpec *ccs = new ChangeCipherSpec();
    printf("Decoding ChangeCipherSpec: %d\n", ccs->decode(p->fragment, p->length));
    this->ProcessClientChangeCipherSpec(ccs);

    delete ccs;
  }

  printf("\n\n");

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
  this->state->pending_read_params->client_version = m->client_version;
  this->state->pending_write_params->client_version = m->client_version;

  this->state->pending_read_params->SetCipher(this->common.BulkCipherAlgorithm());
  this->state->pending_write_params->SetCipher(this->common.BulkCipherAlgorithm());
  this->state->pending_read_params->SetMAC(this->common.MACAlgorithm());
  this->state->pending_write_params->SetMAC(this->common.MACAlgorithm());

  this->state->pending_read_params->client_random[0] = (m->random.gmt_unix_time >> 24) & 0xFF;
  this->state->pending_read_params->client_random[1] = (m->random.gmt_unix_time >> 16) & 0xFF;
  this->state->pending_read_params->client_random[2] = (m->random.gmt_unix_time >> 8) & 0xFF;
  this->state->pending_read_params->client_random[3] = (m->random.gmt_unix_time >> 0) & 0xFF;
  for (size_t i = 0; i < 28; i++) {
    this->state->pending_read_params->client_random[4 + i] = m->random.random_bytes[i];
  }

  for (size_t i = 0; i < 32; i++) {
    this->state->pending_write_params->client_random[i] = this->state->pending_read_params->client_random[i];
  }

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
                                (this->state->pending_write_params->server_random[2] << 8) |
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
  this->client_finished_hash->update(data, length);
  this->server_finished_hash->update(data, length);
  printf("Added to SHA256 state...\n");
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

  // char hex[2 * length + 1];
  // toHex(hex, data, length);
  // hex[2 * length] = '\0';

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
  this->client_finished_hash->update(data, length);
  this->server_finished_hash->update(data, length);
  printf("Added to SHA256 state...\n");
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

  // char hex[2 * length + 1];
  // toHex(hex, data, length);
  // hex[2 * length] = '\0';

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
  this->client_finished_hash->update(data, length);
  this->server_finished_hash->update(data, length);
  printf("Added to SHA256 state...\n");
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

void HandshakeFSM::ProcessClientKeyExchange(ClientKeyExchange *cke) {
  if (this->current_state != 4) {
    return;
  }

  int result = cke->decrypt(this->state, this->config);
  if (result != 0) {
    printf("Bad decryption (%d)!\n", result);
    return;
  }

  uint8_t premaster[48];
  uint8_t seed[77];

  size_t i = 0;
  premaster[0] = cke->client_version.major;
  premaster[1] = cke->client_version.minor;
  for (i = 2; i < 48; i++) {
    premaster[i] = cke->random[i - 2];
  }
  i = 0;
  printf("ClientKeyExchange random: \n");
  for (i = 0; i < 48; i++) {
    printf("%02x", premaster[i]);
  }
  printf("\n");
  i = 0;
  seed[0] = 'm';
  seed[1] = 'a';
  seed[2] = 's';
  seed[3] = 't';
  seed[4] = 'e';
  seed[5] = 'r';
  seed[6] = ' ';
  seed[7] = 's';
  seed[8] = 'e';
  seed[9] = 'c';
  seed[10] = 'r';
  seed[11] = 'e';
  seed[12] = 't';
  printf("Client random: \n");
  for (i = 13; i < 45; i++) {
    seed[i] = this->state->pending_read_params->client_random[i - 13];
    printf("%02x", seed[i]);
  }
  printf("\n");
  printf("Server random: \n");
  for (i = 45; i < 77; i++) {
    seed[i] = this->state->pending_read_params->server_random[i - 45];
    printf("%02x", seed[i]);
  }
  printf("\n");

  prf_sha256 *prf = new prf_sha256(premaster, 48, seed, 77);

  prf->generate(this->state->pending_read_params->master_secret, 48);
  printf("Master Secret: \n");
  for (i = 0; i < 48; i++) {
    this->state->pending_write_params->master_secret[i] = this->state->pending_read_params->master_secret[i];
    printf("%02x", this->state->pending_write_params->master_secret[i]);
  }
  printf("\n");

  delete prf;
  seed[0] = 'k';
  seed[1] = 'e';
  seed[2] = 'y';
  seed[3] = ' ';
  seed[4] = 'e';
  seed[5] = 'x';
  seed[6] = 'p';
  seed[7] = 'a';
  seed[8] = 'n';
  seed[9] = 's';
  seed[10] = 'i';
  seed[11] = 'o';
  seed[12] = 'n';
  printf("Server random: \n");
  for (i = 0; i < 32; i++) {
    seed[i + 13] = this->state->pending_read_params->server_random[i];
    printf("%02x", seed[i + 13]);
  }
  printf("\n");
  printf("Client random: \n");
  for (i = 0; i < 32; i++) {
    seed[i + 45] = this->state->pending_read_params->client_random[i];
    printf("%02x", seed[i + 45]);
  }
  printf("\n");

  prf_sha256 *prf_2 = new prf_sha256(this->state->pending_read_params->master_secret, 48, seed, 77);

  uint8_t keydata[128];
  prf_2->generate(keydata, 128);

  size_t k_p = 0;

  printf("rm: %d, wm: %d, rc: %d, wc: %d\n", this->state->pending_read_params->mac_key_length,
         this->state->pending_write_params->mac_key_length, this->state->pending_read_params->enc_key_length,
         this->state->pending_write_params->enc_key_length);

  this->state->pending_read_params->mac_key =
      (uint8_t *)malloc(sizeof(uint8_t) * this->state->pending_read_params->mac_key_length);
  this->state->pending_write_params->mac_key =
      (uint8_t *)malloc(sizeof(uint8_t) * this->state->pending_write_params->mac_key_length);
  this->state->pending_read_params->cipher_key =
      (uint8_t *)malloc(sizeof(uint8_t) * this->state->pending_read_params->enc_key_length);
  this->state->pending_write_params->cipher_key =
      (uint8_t *)malloc(sizeof(uint8_t) * this->state->pending_write_params->enc_key_length);

  for (i = 0; i < this->state->pending_read_params->mac_key_length; i++) {
    this->state->pending_read_params->mac_key[i] = keydata[k_p];
    k_p++;
  }

  for (i = 0; i < this->state->pending_write_params->mac_key_length; i++) {
    this->state->pending_write_params->mac_key[i] = keydata[k_p];
    k_p++;
  }

  printf("Read key: \n");
  for (i = 0; i < this->state->pending_read_params->enc_key_length; i++) {
    this->state->pending_read_params->cipher_key[i] = keydata[k_p];
    printf("%02x", keydata[k_p]);
    k_p++;
  }
  printf("\n");

  printf("Write key: \n");
  for (i = 0; i < this->state->pending_write_params->enc_key_length; i++) {
    this->state->pending_write_params->cipher_key[i] = keydata[k_p];
    printf("%02x", keydata[k_p]);
    k_p++;
  }
  printf("\n");

  delete prf;

  this->current_state = 5;
}

void HandshakeFSM::ProcessClientChangeCipherSpec(ChangeCipherSpec *ccs) {
  if (this->current_state != 5) {
    printf("Bad state %d!\n", this->current_state);
    return;
  }

  if (ccs->value == ChangeCipherSpec_e::change_cipher_spec) {
    this->state->SwitchReadState();
    this->current_state = 6;

    printf("Switched read states.\n");
  } else {
    printf("Refusing to switch states.\n");
  }
}

void HandshakeFSM::ProcessClientFinished(Finished *f) {
  if (this->current_state != 6) {
    printf("Bad state %d!\n", this->current_state);
    return;
  }

  printf("Finished check (%d): \n", f->verify_data_length);
  for (size_t i = 0; i < f->verify_data_length; i++) {
    printf("%02x", f->verify_data[i]);
  }
  printf("\n");

  uint8_t hash_data[15 + this->client_finished_hash->output_size];
  this->client_finished_hash->finalize(&(hash_data[15]));
  hash_data[0] = 'c';
  hash_data[1] = 'l';
  hash_data[2] = 'i';
  hash_data[3] = 'e';
  hash_data[4] = 'n';
  hash_data[5] = 't';
  hash_data[6] = ' ';
  hash_data[7] = 'f';
  hash_data[8] = 'i';
  hash_data[9] = 'n';
  hash_data[10] = 'i';
  hash_data[11] = 's';
  hash_data[12] = 'h';
  hash_data[13] = 'e';
  hash_data[14] = 'd';

  prf_sha256 *prf = new prf_sha256(this->state->current_read_params->master_secret, 48, hash_data,
                                   15 + this->client_finished_hash->output_size);

  uint8_t verify_data[f->verify_data_length];
  prf->generate(verify_data, f->verify_data_length);

  bool verify_ok = true;

  printf("Server Side Validation (%d): \n", f->verify_data_length);
  for (size_t i = 0; i < f->verify_data_length; i++) {
    printf("%02x", verify_data[i]);
    verify_ok = verify_ok && (verify_data[i] == f->verify_data[i]);
  }
  printf("\n");

  if (verify_ok) {
    this->current_state = 7;
    this->ProcessServerChangeCipherSpec();
  }
}

void HandshakeFSM::ProcessServerChangeCipherSpec() {
  if (this->current_state != 7) {
    printf("Bad state %d!\n", this->current_state);
    return;
  }

  this->current_state = 8;
  this->ProcessServerFinished();
}

void HandshakeFSM::ProcessServerFinished() {
  if (this->current_state != 8) {
    printf("Bad state %d!\n", this->current_state);
    return;
  }

  this->current_state = 9;
}
