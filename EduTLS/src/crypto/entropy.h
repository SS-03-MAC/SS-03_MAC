//===-- EduTLS/src/crypto/entropy.h                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains common utility methods for getting secure entropy from
/// the system.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>

#ifdef __linux__
#include <errno.h>
#include <exception>
#include <linux/random.h>
#include <syscall.h>
#include <unistd.h>

static inline void edutls_rand_check(uint8_t *buffer, int result, int err) {
  if (result == -1) {
    switch (err) {
    case EAGAIN:
    case EINTR:
      sleep(1);
      result = syscall(SYS_getrandom, buffer, 255, 0);
      edutls_rand_check(buffer, result, errno);
      break;
    case EINVAL:
      throw EINVAL;
      break;
    case EFAULT:
      throw EFAULT;
      break;
    default:
      throw - 1;
    }
  } else if (result != 255) {
    sleep(1);
    result = syscall(SYS_getrandom, buffer, 255, 0);
    edutls_rand_check(buffer, result, errno);
  }
}

static inline void edutls_rand_bytes(uint8_t *output, size_t count) {
  size_t o_p = 0;
  size_t b_p = 0;
  uint8_t buffer[255];
  int result = syscall(SYS_getrandom, buffer, 255, 0);
  edutls_rand_check(buffer, result, errno);

  while (o_p < count) {
    output[o_p] = buffer[b_p];
    o_p += 1;
    b_p += 1;

    if (o_p != count) {
      if (b_p == 255) {
        b_p = 0;

        int result = syscall(SYS_getrandom, buffer, 255, 0);
        edutls_rand_check(buffer, result, errno);
      }
    }
  }
}

#endif
