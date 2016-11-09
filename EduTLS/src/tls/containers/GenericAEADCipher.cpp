//===-- EduTLS/src/tls/containers/GenericAEADCipher.cpp   -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the Generic AEAD Cipher
/// protocol.
///
//===----------------------------------------------------------------------===//

#include "./GenericAEADCipher.h"
#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

GenericAEADCipher::GenericAEADCipher(TLSSession *state) { this->state = state; }
GenericAEADCipher::~GenericAEADCipher() {}

int GenericAEADCipher::encode(uint8_t *) { return 0; }
size_t GenericAEADCipher::encode_length() { return 0; }
int GenericAEADCipher::decode(uint8_t *, size_t) { return 0; }
