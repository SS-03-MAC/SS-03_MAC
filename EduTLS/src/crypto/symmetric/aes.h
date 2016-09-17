//===-- EduTLS/src/crypto/symmetric/aes.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the AES class which is a specific
/// implementation of the symmetric cipher class.
///
//===----------------------------------------------------------------------===//

#include "symmetric.h"

#ifndef EDUTLS_SRC_CRYPTO_SYMMETRIC_AES_H__
#define EDUTLS_SRC_CRYPTO_SYMMETRIC_AES_H__

class aes : public symmetric {
private:
  uint8_t size;
  uint32_t *s_key;
  uint8_t block[16];
};

#endif /* end of include guard: EDUTLS_SRC_CRYPTO_SYMMETRIC_AES_H__ */
