//===-- EduTLS/src/tls/abstractions/Packet.h              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Packet class declaration..
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>
#include <cstdlib>

class Packet {
public:
  size_t length;
  uint8_t *data;

  Packet(uint8_t *data, size_t length);
  ~Packet();
};
