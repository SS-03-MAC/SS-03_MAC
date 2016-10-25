//===-- EduTLS/src/tls/messages/SignatureHashAlgorithm.h  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Signature and Hash Algorithm
/// protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/HashAlgorithm.h"
#include "../enums/SignatureAlgorithm.h"
#include "../interfaces/encodable.h"

class SignatureAndHashAlgorithm final : public encodable_i {
public:
  HashAlgorithm_e hash;
  SignatureAlgorithm_e signature;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
