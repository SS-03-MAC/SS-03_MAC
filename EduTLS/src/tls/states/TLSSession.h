//===-- EduTLS/src/tls/states/TLSSession.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the TLS Session protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./ConnectionStates.h"
#include "./SecurityParameters.h"
#include <cstdint>
#include <cstdlib>

class TLSSession {
private:
  size_t session_id_length;
  uint8_t *session_id;

  bool established;
  int renegotation_state;

  ConnectionEnd_e entity;

  SecurityParameters *current_read_params;
  SecurityParameters *current_write_params;
  SecurityParameters *pending_read_params;
  SecurityParameters *pending_write_params;

  ConnectionStates *current_read;
  ConnectionStates *current_write;
  ConnectionStates *pending_read;
  ConnectionStates *pending_write;

  size_t write_mac_key_length;
  uint8_t *write_mac_key;
  size_t read_mac_key_length;
  uint8_t *read_mac_key;
  size_t read_encryption_key_length;
  uint8_t *read_encryption_key;
  size_t write_encryption_key_length;
  uint8_t *write_encryption_key;
  size_t read_encryption_iv_length;
  uint8_t *read_encryption_iv;
  size_t write_encryption_iv_length;
  uint8_t *write_encryption_iv;

public:
  TLSSession(ConnectionEnd_e entity);
  ~TLSSession();

  int SwitchStates();
};
