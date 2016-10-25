//===-- EduTLS/src/tls/messages/ProtocolVersion.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Protocol Version protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../interfaces/encodable.h"
#include <cstdint>

class ProtocolVersion_t final {
public:
  uint8_t major;
  uint8_t minor;
};
