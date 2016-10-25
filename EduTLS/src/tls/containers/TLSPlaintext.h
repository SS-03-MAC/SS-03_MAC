//===-- EduTLS/src/tls/containers/TLSPlaintext.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the TLS Plaintext protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ContentType.h"
#include "../interfaces/encodable.h"
#include "../messages/ProtocolVersion.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

class TLSPlaintext final : public encodable_i {
public:
  uint16_t length;
  uint8_t *fragment;

  TLSPlaintext();
  TLSPlaintext(uint16_t length, uint8_t *fragment);
  ~TLSPlaintext();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
