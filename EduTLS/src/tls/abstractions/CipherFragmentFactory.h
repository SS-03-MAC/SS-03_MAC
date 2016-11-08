//===--EduTLS/src/tls/abstractions/CipherFragmentFactory.h-------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Cipher Fragment Factory class declaration..
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
#include "../states/TLSSession.h"

class CipherFragment_f {
public:
  static inline CipherFragment_t *Construct(CipherType_e type, TLSSession *state) {
    switch (type) {
    case CipherType_e::stream:
      return new GenericStreamCipher(state);
      break;
    case CipherType_e::block:
      return new GenericBlockCipher(state);
      break;
    case CipherType_e::aead:
      return new GenericAEADCipher(state);
      break;
    }

    return NULL;
  };

  static inline CipherFragment_t *Construct(CipherType_e type, TLSCompressed *c, TLSSession *state) {
    switch (type) {
    case CipherType_e::stream:
      return new GenericStreamCipher(state, c);
      break;
    case CipherType_e::block:
      return new GenericBlockCipher(state, c);
      break;
    case CipherType_e::aead:
      return new GenericAEADCipher(state);
      break;
    }

    return NULL;
  };
};
