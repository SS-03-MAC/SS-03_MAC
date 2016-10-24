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

#include "../enums/Alert.h"

class Alert {
public:
  AlertLevel_t level;
  AlertDescription_t description;
};
