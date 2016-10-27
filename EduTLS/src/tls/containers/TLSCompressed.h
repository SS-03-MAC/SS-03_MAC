//===-- EduTLS/src/tls/containers/TLSCompressed.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the TLS Compressed protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ContentType.h"
#include "../interfaces/encodable.h"
#include "../messages/ProtocolVersion.h"
#include "../states/TLSSession.h"
#include "./TLSPlaintext.h"

class TLSCompressed final : public encodable_i {
public:
  uint16_t length;
  TLSPlaintext *contents;

  TLSSession *state;

  TLSCompressed(TLSSession *state);
  TLSCompressed(TLSSession *state, TLSPlaintext *contents);
  ~TLSCompressed();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
