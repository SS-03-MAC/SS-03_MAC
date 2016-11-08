//===-- EduTLS/src/tls/messages/Random.cpp                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message implementation for the Random protocol.
///
//===----------------------------------------------------------------------===//

#include "Random.h"
#include "../interfaces/encodable.h"

Random_t::Random_t() {}
Random_t::Random_t(uint32_t gmt_unix_time, uint8_t random_bytes[28]) {
  this->gmt_unix_time = gmt_unix_time;
  size_t i = 0;
  for (i = 0; i < 28; i++) {
    this->random_bytes[i] = random_bytes[i];
  }
};
Random_t::~Random_t() {}

int Random_t::encode(uint8_t *result) {
  result[0] = (this->gmt_unix_time >> 24) & 0xFF;
  result[1] = (this->gmt_unix_time >> 16) & 0xFF;
  result[2] = (this->gmt_unix_time >> 8) & 0xFF;
  result[3] = this->gmt_unix_time & 0xFF;
  size_t i = 0;
  for (i = 0; i < 28; i++) {
    result[i + 4] = this->random_bytes[i];
  }
  return 0;
}
size_t Random_t::encode_length() { return 32; }
int Random_t::decode(uint8_t *encoded, size_t length) {
  this->gmt_unix_time = (encoded[0] << 24) | (encoded[1] << 16) | (encoded[2] << 8) | encoded[3];
  size_t i = 0;
  for (i = 4; i < 32 && i < length; i++) {
    this->random_bytes[i - 4] = encoded[i];
  }
  return 0;
}
