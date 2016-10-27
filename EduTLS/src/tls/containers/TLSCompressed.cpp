//===-- EduTLS/src/tls/containers/TLSCompressed.cpp       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the TLS Compressed protocol.
///
//===----------------------------------------------------------------------===//

#include "./TLSCompressed.h"
#include "../states/TLSSession.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

TLSCompressed::TLSCompressed(TLSSession *state) {
  this->contents = NULL;
  this->state = state;
}

TLSCompressed::TLSCompressed(TLSSession *state, TLSPlaintext *contents) {
  this->length = contents->length;
  this->contents = contents;
  this->state = state;
}

TLSCompressed::~TLSCompressed() {}

int TLSCompressed::encode(uint8_t *result) {
  this->contents->encode(result);
  return 0;
}

size_t TLSCompressed::encode_length() { return this->contents->encode_length(); }

int TLSCompressed::decode(uint8_t *encoded, size_t length) {
  this->contents = new TLSPlaintext();

  this->contents->decode(encoded, length);
  return 0;
}
