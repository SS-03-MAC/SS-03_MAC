//===-- EduTLS/src/tls/messages/ChangeCipherSpec.h        -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Change Cipher Spec protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enums/ChangeCipherSpec.h"

class ChangeCipherSpec {
public:
  ChangeCipherSpec_t value;
};
