//===-- EduTLS/src/tls/utils.h                            -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains various utilities for use with TLS
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>

struct uint24_t {
  uint32_t value : 24;
};
