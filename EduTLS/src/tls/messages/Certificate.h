//===-- EduTLS/src/tls/messages/Certificate.h             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Certificate protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "Handshake.h"

#include <cstdint>

class Certificate_t final : public encodable_i {
public:
  uint32_t certificate_length : 24;
  uint8_t *certificate_data;

  Certificate_t();
  ~Certificate_t();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};

class Certificate final : public HandshakeContents_t {
public:
  size_t certificates_length;
  Certificate_t *certificates;

  Certificate();
  ~Certificate();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
