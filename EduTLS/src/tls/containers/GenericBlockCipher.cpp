//===-- EduTLS/src/tls/containers/GenericBlockCipher.cpp  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementations for the Generic Block Cipher
/// protocol.
///
//===----------------------------------------------------------------------===//

#include "./GenericBlockCipher.h"
#include "../states/TLSSession.h"
#include "./TLSCiphertext.h"
#include "./TLSCompressed.h"
#include "./TLSPlaintext.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

GenericBlockCipher::GenericBlockCipher(TLSSession *state) { this->state = state; }
GenericBlockCipher::~GenericBlockCipher() {}

int GenericBlockCipher::encode(uint8_t *) { return 0; }
size_t GenericBlockCipher::encode_length() { return 0; }
int GenericBlockCipher::decode(uint8_t *, size_t) { return 0; }
