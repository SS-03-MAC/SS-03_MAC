//===-- EduTLS/src/tls/messages/ServerDHParams.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Hello Request protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "./ServerKeyExchange.h"

class ServerDHParams final : public ServerKeyExchange {
public:
  size_t dh_p_length;
  uint8_t *dh_p;
  size_t dh_g_length;
  uint8_t *dh_g;
  size_t dh_Ys_length;
  uint8_t *dh_Ys;
  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
