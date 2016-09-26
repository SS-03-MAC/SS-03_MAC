//===-- EduTLS/src/crypto/hash/sha2-224.h                 -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of sha2-224, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

class sha2_224 final : public md {
private:
  uint32_t h[8];

  void core();
  void digest(uint8_t *output);

  uint32_t ch(uint32_t x, uint32_t y, uint32_t z);
  uint32_t mj(uint32_t x, uint32_t y, uint32_t z);
  uint32_t bsig0(uint32_t x);
  uint32_t bsig1(uint32_t x);
  uint32_t ssig0(uint32_t x);
  uint32_t ssig1(uint32_t x);

public:
  void init();
};
