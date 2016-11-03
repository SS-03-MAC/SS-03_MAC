//===-- EduTLS/src/crypto/hash/prf_sha256.h               -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the PRF SHA256 class.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include <cstdint>

#include "./hash.h"
#include "./hmac.h"
#include "./sha2-256.h"

class prf_sha256 final {
private:
  sha2_256 hasher;
  hmac *h;

  uint8_t *secret;
  uint8_t *seed;
  uint8_t *A;

  size_t secret_length;
  size_t seed_length;

public:
  prf_sha256(uint8_t *secret, size_t secret_length, uint8_t *seed, size_t seed_length);
  ~prf_sha256();

  void generate(uint8_t *output, size_t length);
};
