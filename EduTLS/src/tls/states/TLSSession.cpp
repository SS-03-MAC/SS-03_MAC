//===-- EduTLS/src/tls/states/TLSSession.cpp              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state implementations for the TLS Session protocol.
///
//===----------------------------------------------------------------------===//

#include "TLSSession.h"

TLSSession::TLSSession(ConnectionEnd_e entity) {
  this->session_id = NULL;
  this->entity = entity;

  this->established = false;

  this->current_read_params = new SecurityParameters();
  this->current_read_params->entity = entity;

  this->current_write_params = new SecurityParameters();
  this->current_write_params->entity = entity;

  this->pending_read_params = NULL;
  this->pending_write_params = NULL;
}

TLSSession::~TLSSession() {
  if (this->session_id != NULL) {
    free(this->session_id);
  }

  if (this->current_read_params != NULL) {
    delete this->current_read_params;
  }

  if (this->current_write_params != NULL) {
    delete this->current_write_params;
  }

  if (this->pending_read_params != NULL) {
    delete this->pending_read_params;
  }

  if (this->pending_write_params != NULL) {
    delete this->pending_write_params;
  }
}

int TLSSession::SwitchStates() {
  if (this->pending_read_params != NULL && this->pending_write_params != NULL) {
    if (this->current_read_params != NULL) {
      delete this->current_read_params;
    }

    if (this->current_write_params != NULL) {
      delete this->current_write_params;
    }

    this->current_read_params = this->pending_read_params;
    this->current_write_params = this->pending_write_params;

    this->pending_read_params = NULL;
    this->pending_write_params = NULL;

    return 0;
  }

  return 1;
}
