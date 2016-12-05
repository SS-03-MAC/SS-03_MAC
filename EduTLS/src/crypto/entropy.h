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
#include <cstdio>
#include <cstdlib>

#ifdef __APPLE__

static inline void edutls_rand_read_raw(uint8_t *output) {
  /*
   Per: https://developer.apple.com/library/content/documentation/Security/Conceptual
        /cryptoservices/RandomNumberGenerationAPIs/RandomNumberGenerationAPIs.html
  */
  FILE *fp = fopen("/dev/random", "r");
  size_t i = 0;

  if (!fp) {
    perror("randgetter");
    exit(-1);
  }

  for (i = 0; i < 255; i++) {
    output[i] = fgetc(fp);
  }

  fclose(fp);
}

static inline void edutls_rand_bytes(uint8_t *output, size_t count) {
  size_t o_p = 0;
  size_t b_p = 0;
  uint8_t buffer[255];
  edutls_rand_read_raw(buffer);

  while (o_p < count) {
    output[o_p] = buffer[b_p];
    o_p += 1;
    b_p += 1;

    if (o_p != count) {
      if (b_p == 255) {
        b_p = 0;

        edutls_rand_read_raw(buffer);
      }
    }
  }
}
#endif

#ifdef __linux__
#include <errno.h>
#include <exception>
#include <linux/random.h>
#include <syscall.h>
#include <unistd.h>

#ifdef NOTDEF // SYS_getrandom

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
      perror("[edutls_rand_check] Invalid flags supplied to getrandom()");
      exit(-1);
      break;
    case EFAULT:
      perror("[edutls_rand_check] Fault in getrandom()");
      exit(-1);
      break;
    default:
      perror("[edutls_rand_check] Unknown errno number");
      exit(-1);
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
#else
static inline void edutls_rand_read_raw(uint8_t *output) {
  FILE *fp = fopen("/dev/urandom", "r");
  size_t i = 0;

  if (!fp) {
    perror("randgetter");
    exit(-1);
  }

  for (i = 0; i < 255; i++) {
    output[i] = fgetc(fp);
  }

  fclose(fp);
}

static inline void edutls_rand_bytes(uint8_t *output, size_t count) {
  size_t o_p = 0;
  size_t b_p = 0;
  uint8_t buffer[255];
  edutls_rand_read_raw(buffer);

  while (o_p < count) {
    output[o_p] = buffer[b_p];
    o_p += 1;
    b_p += 1;

    if (o_p != count) {
      if (b_p == 255) {
        b_p = 0;

        edutls_rand_read_raw(buffer);
      }
    }
  }
}
#endif
#endif

#ifdef __CYGWIN__
static inline void edutls_rand_read_raw(uint8_t *output) {
  FILE *fp = fopen("/dev/urandom", "r");
  size_t i = 0;

  if (!fp) {
    perror("randgetter");
    exit(-1);
  }

  for (i = 0; i < 255; i++) {
    output[i] = fgetc(fp);
  }

  fclose(fp);
}

static inline void edutls_rand_bytes(uint8_t *output, size_t count) {
  size_t o_p = 0;
  size_t b_p = 0;
  uint8_t buffer[255];
  edutls_rand_read_raw(buffer);

  while (o_p < count) {
    output[o_p] = buffer[b_p];
    o_p += 1;
    b_p += 1;

    if (o_p != count) {
      if (b_p == 255) {
        b_p = 0;

        edutls_rand_read_raw(buffer);
      }
    }
  }
}
#endif
