//===-- EduTLS/src/tls/enums/SignatureAlgorithm.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Signature Algorithm protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

enum class SignatureAlgorithm_t { anonymous = 0, rsa = 1, dsa = 2, ecdsa = 3, max = 255 };
