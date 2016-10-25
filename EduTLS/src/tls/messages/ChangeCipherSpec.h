//===-- EduTLS/src/tls/messages/ChangeCipherSpec.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Change Cipher Spec protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ChangeCipherSpec.h"
#include "../interfaces/encodable.h"

class ChangeCipherSpec final : public encodable_i {
public:
  ChangeCipherSpec_e value;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded);
};
