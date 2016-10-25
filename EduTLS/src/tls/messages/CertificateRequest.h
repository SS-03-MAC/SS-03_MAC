//===-- EduTLS/src/tls/messages/CertificateRequest.h      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Certificate Request protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include "Handshake.h"
#include "SignatureHashAlgorithm.h"

class CertificateRequest final : public HandshakeContents_t {
  size_t certificate_types_length;
  ClientCertificateType_e *certificate_types;
  size_t supported_signature_algorithms_length;
  SignatureAndHashAlgorithm *supported_signature_algorithms;
  size_t certificate_authorities_length;
  uint8_t *certificate_authorities;

  int encode(uint8_t *result);
  size_t encode_length();
  int decode(uint8_t *encoded, size_t length);
};
