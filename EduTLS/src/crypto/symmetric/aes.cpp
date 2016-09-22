//===-- EduTLS/src/crypto/symmetric/aes.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the AES class methods.
///
//===----------------------------------------------------------------------===//

#include "aes.h"
#include <cstdint>

aes::aes(uint8_t *key, size_t size) {}

aes *aes::aes_128(uint8_t key[16]) { return new aes(key, 16); }

aes *aes::aes_192(uint8_t key[24]) { return new aes(key, 24); }

aes *aes::aes_256(uint8_t key[32]) { return new aes(key, 32); }
