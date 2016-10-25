//===-- EduTLS/src/tls/messages/DigitallySigned.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Digitally Signed protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "./SignatureHashAlgorithm.h"

class DigitallySigned final : public encodable_i {
  SignatureAndHashAlgorithm algorithm;
  size_t signature_length;
  uint8_t *signature;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
