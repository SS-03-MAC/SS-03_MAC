//===-- EduTLS/src/tls/enums/ChangeCipherSpec.h           -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Change Cipher Spec protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

enum ChangeCipherSpec_t { change_cipher_spec = 1, keep_cipher_spec = 255 };
