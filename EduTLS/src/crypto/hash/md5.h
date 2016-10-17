//===-- EduTLS/src/crypto/hash/md5.h                      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of MD5, an instance of a
/// Merkle–Damgård hash function.
///
//===----------------------------------------------------------------------===//

#include "hash.h"
#include "md.h"

#include <cstddef>
#include <cstdint>

class md5 final : public md {
private:
  uint32_t s[4];

  void core();
  void digest(uint8_t *output);

  uint32_t f(uint32_t X, uint32_t Y, uint32_t Z);
  uint32_t g(uint32_t X, uint32_t Y, uint32_t Z);
  uint32_t h(uint32_t X, uint32_t Y, uint32_t Z);
  uint32_t i(uint32_t X, uint32_t Y, uint32_t Z);

public:
  void init();
};
