//===-- EduTLS/src/tls/abstractions/PacketQueue.cpp       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the Packet Queue class implementation..
///
//===----------------------------------------------------------------------===//

#include "./PacketQueue.h"
#include "./Packet.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cstring>
#include <iostream>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

PacketQueue::PacketQueue(int socket, int offset, int length) {
  this->socket = socket;
  this->size_offset = offset;
  this->size_length = length;

  this->buffer_offset = 0;
  this->buffer_length = 131072;

  size_t i = 0;
  for (i = 0; i < this->buffer_length; i++) {
    this->buffer[i] = 0;
  }
}

PacketQueue::~PacketQueue() {
  size_t i = 0;
  for (i = 0; i < this->buffer_length; i++) {
    this->buffer[i] = 0;
  }
}

int PacketQueue::Read() {
  ssize_t read_length =
      read(this->socket, &(this->buffer[this->buffer_offset]), this->buffer_length - this->buffer_offset);

  if (read_length <= 0) {
    return -1;
  }

  this->buffer_offset += read_length;

  while (this->buffer_offset < this->size_offset + this->size_length) {
    read_length = read(this->socket, &(this->buffer[this->buffer_offset]), this->buffer_length - this->buffer_offset);

    if (read_length <= 0) {
      return -1;
    }

    this->buffer_offset += read_length;
  }

  size_t length = 0;
  size_t i = 0;
  for (i = 0; i < this->size_length; i++) {
    length = length << 8;
    length = length | this->buffer[this->size_offset + i];
  }

  while (this->buffer_offset > length) {
    size_t packet_length = length + this->size_offset + this->size_length;
    Packet *p = new Packet(this->buffer, packet_length);
    this->data.push(p);

    for (i = packet_length; i < this->buffer_offset; i++) {
      this->buffer[i - packet_length] = this->buffer[i];
    }

    this->buffer_offset -= packet_length;
    for (i = this->buffer_offset; i < this->buffer_length; i++) {
      this->buffer[i] = 0x00;
    }

    if (this->buffer_offset >= this->size_offset + this->size_length) {
      length = 0;
      for (i = 0; i < this->size_length; i++) {
        length = length << 8;
        length = length | this->buffer[this->size_offset + i];
      }
    } else {
      length = this->buffer_length;
    }
  }

  return 0;
}

size_t PacketQueue::ReadPacket(uint8_t *packet) {
  while (this->data.size() == 0) {
    if (this->Read() == -1) {
      return 0;
    }
  }

  Packet *p = this->data.front();
  this->data.pop();
  size_t length = p->length;
  size_t i = 0;
  for (i = 0; i < length; i++) {
    packet[i] = p->data[i];
  }

  delete p;

  return length;
}

size_t PacketQueue::PeekPacket(uint8_t *packet) {
  while (this->data.size() == 0) {
    this->Read();
  }

  Packet *p = this->data.front();
  size_t length = p->length;
  size_t i = 0;
  for (i = 0; i < length; i++) {
    packet[i] = p->data[i];
  }

  return length;
}

void PacketQueue::WritePacket(uint8_t *data, size_t length) {
  int n = write(this->socket, data, length);

  if (n < 0) {
    printf("Error writing to socket!\n\n");
  }
}
