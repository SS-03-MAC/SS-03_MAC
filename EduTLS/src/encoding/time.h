//===-- EduTLS/src/encoding/time.h                        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a date/time structure for use with UTCTime.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>

struct UTCTime {
  uint16_t year;
  uint8_t month;
  uint8_t day;

  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};
