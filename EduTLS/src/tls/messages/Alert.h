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
#include "../interfaces/encodable.h"

class Alert : public encodable_i {
public:
  AlertLevel_t level;
  AlertDescription_t description;
};
