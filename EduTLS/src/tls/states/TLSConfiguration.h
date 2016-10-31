//===-- EduTLS/src/tls/states/TLSConfiguration.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the TLS Configuration protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../containers/CipherSuite.h"
#include "../messages/Certificate.h"

class TLSConfiguration {
public:
  bool debug;

  size_t SupportedCipherSuitesLength;
  CipherSuite *SupportedCipherSuites;

  Certificate_t cert;

  TLSConfiguration() {
    uint8_t supported[20] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x3B, 0x00, 0x04, 0x00, 0x05,
                             0x00, 0x0A, 0x00, 0x2F, 0x00, 0x35, 0x00, 0x3C, 0x00, 0x3D};
    this->debug = false;
    this->SupportedCipherSuites = CipherSuite::FromUint8(supported, 20);
    this->SupportedCipherSuitesLength = 10;
  }
};
