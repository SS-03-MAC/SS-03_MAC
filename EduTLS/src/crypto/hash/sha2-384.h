//===-- EduTLS/src/crypto/hash/sha2-384.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of SHA2-384, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

class sha2_384 final : public md {
private:
  uint64_t h[8];

  void core();
  void digest(uint8_t *output);

  uint64_t ch(uint64_t x, uint64_t y, uint64_t z);
  uint64_t mj(uint64_t x, uint64_t y, uint64_t z);
  uint64_t bsig0(uint64_t x);
  uint64_t bsig1(uint64_t x);
  uint64_t ssig0(uint64_t x);
  uint64_t ssig1(uint64_t x);

public:
  void init();
};
