//===-- EduTLS/src/tls/abstractions/Packet.h              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Packet class declaration..
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>
#include <cstdlib>

#include "../containers/GenericAEADCipher.h"
#include "../containers/GenericBlockCipher.h"
#include "../containers/GenericStreamCipher.h"
#include "../containers/TLSCiphertext.h"
#include "../enums/ConnectionStates.h"

class CipherFragment_f {
public:
  static inline CipherFragment_t Construct(CipherType_e type) {
    CipherFragment_t *result;
    switch (type) {
    case CipherType_e::stream:
      result = new GenericStreamCipher();
    case CipherType_e::block:
      result = new GenericBlockCipher();
    case CipherType_e::aead:
      result = new GenericAEADCipher();
      break;
    }

    return result;
  };
};
