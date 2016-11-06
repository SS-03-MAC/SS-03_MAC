//===--EduTLS/src/tls/abstractions/HMACFactory.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the HMAC Factory class declaration..
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>
#include <cstdlib>

#include "../../crypto/crypto.h"
#include "../containers/TLSCiphertext.h"
#include "../enums/ConnectionStates.h"
#include "../states/TLSSession.h"

class HMAC_f {
public:
  static inline hmac *Construct(MACAlgorithm_e type, TLSSession *state) {
    hash *h = NULL;
    switch (type) {
    case MACAlgorithm_e::hmac_md5:
      h = new md5();
      break;
    case MACAlgorithm_e::hmac_sha1:
      h = new sha1();
      break;
    case MACAlgorithm_e::hmac_sha256:
      h = new sha2_256();
      break;
    case MACAlgorithm_e::hmac_sha384:
      h = new sha2_384();
      break;
    case MACAlgorithm_e::hmac_sha512:
      h = new sha2_512();
      break;
    default:
      break;
    }

    if (h == NULL) {
      return NULL;
    }

    h->init();
    return new hmac(h, state->current_read_params->mac_key, state->current_read_params->mac_key_length);

    return NULL;
  };
};
