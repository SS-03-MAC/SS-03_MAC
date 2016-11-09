//===--EduTLS/src/tls/abstractions/SendingFactory.h       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Sending Factory class declaration.
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
#include "./CipherFragmentFactory.h"

class Sending_f {
public:
  static inline TLSCiphertext *Construct(ContentType_e type, uint8_t *data, size_t data_length, TLSSession *state) {
    TLSPlaintext *p = new TLSPlaintext(data_length, data);
    TLSCompressed *c = new TLSCompressed(state, p);
    CipherFragment_t *cft = CipherFragment_f::Construct(state->current_write_params->cipher_type, c, state);

    cft->version.major = state->current_write_params->client_version.major;
    cft->version.minor = state->current_write_params->client_version.minor;

    cft->type = type;

    TLSCiphertext *m = new TLSCiphertext(state, cft);

    m->version.major = state->current_write_params->client_version.major;
    m->version.minor = state->current_write_params->client_version.minor;

    m->type = type;

    return m;
  };
};
