//===-- EduTLS/src/tls/abstractions/Packet.cpp            -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Packet class implementation..
///
//===----------------------------------------------------------------------===//

#include "./Packet.h"

#include <cstdint>
#include <cstdlib>

Packet::Packet(uint8_t *data, size_t length) {
  this->data = new uint8_t[length];
  size_t i = 0;
  for (i = 0; i < length; i++) {
    this->data[i] = data[i];
  }

  this->length = length;
}

Packet::~Packet() { delete[] this->data; }
