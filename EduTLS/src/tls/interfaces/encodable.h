//===-- EduTLS/src/tls/interfaces/encodable.h             -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the Encodable interface.
///
//===----------------------------------------------------------------------===//

#pragma once

class encodable_i {
  virtual int encode(uint8_t *result) = 0;
  virtual size_t encode_length() = 0;
  virtual int decode(uint8_t *encoded) = 0;
};
