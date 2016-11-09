//===-- EduTLS/src/crypto/hash/sha1.h                     -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of SHA1, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

class sha1 final : public md {
private:
  uint32_t h[5];

  void core();
  void digest(uint8_t *output);

  uint32_t f(uint8_t t, uint32_t B, uint32_t C, uint32_t D);
  uint32_t k(uint8_t t);

public:
  void init();
};
