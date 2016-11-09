//===-- EduTLS/src/tls/messages/Finished.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Finished protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "./Handshake.h"

class Finished final : public HandshakeContents_t {
public:
  uint8_t verify_data_length;
  uint8_t *verify_data;

  Finished();
  ~Finished();

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
