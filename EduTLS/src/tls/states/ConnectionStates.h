//===-- EduTLS/src/tls/states/ConnectionStates.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the Security Parameters protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./CipherState.h"
#include "./CompressionState.h"
#include "./MACKey.h"

#include <cstdint>
#include <cstdlib>

class ConnectionStates {
public:
  CompressionState_t *compression;
  CipherState_t *cipher;
  MACKey_t *mac_key;

  size_t sequence_number;
};
