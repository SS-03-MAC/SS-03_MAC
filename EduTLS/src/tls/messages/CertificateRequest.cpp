//===-- EduTLS/src/tls/messages/CertificateRequest.cpp     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Server Key Exchange protocol.
///
//===----------------------------------------------------------------------===//

#include "CertificateRequest.h"
#include <cstdint>

CertificateRequest::CertificateRequest() {}
CertificateRequest::~CertificateRequest() {}

int CertificateRequest::encode(uint8_t *) { return 0; }
size_t CertificateRequest::encode_length() { return 0; }
int CertificateRequest::decode(uint8_t *, size_t) { return 0; }
