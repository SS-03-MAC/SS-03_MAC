//===-- EduTLS/src/tls/abstractions/PacketQueue.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Packet Queue class declaration..
///
//===----------------------------------------------------------------------===//

#pragma once
#include <cstdint>
#include <cstdlib>
#include <queue>

#include "./Packet.h"

class PacketQueue {
private:
  int socket;

  std::queue<Packet *> data;

  size_t buffer_offset;
  size_t buffer_length;
  uint8_t buffer[131072];

  size_t size_offset;
  size_t size_length;

  int Read();

public:
  PacketQueue(int socket, int offset, int length);
  ~PacketQueue();

  size_t ReadPacket(uint8_t *packet);
  size_t PeekPacket(uint8_t *packet);
  void WritePacket(uint8_t *data, size_t length);
};
