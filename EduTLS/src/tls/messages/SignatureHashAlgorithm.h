//===-- EduTLS/src/tls/messages/SignatureHashAlgorithm.h  -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message classes for the Signature and Hash Algorithm
/// protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../enum/HashAlgorithm.h"
#include "../enum/SignatureAlgorithm.h"
#include "../interfaces/encodable.h"

class SignatureAndHashAlgorithm_t : public encodable_i {
  HashAlgorithm_t hash;
  SignatureAlgorithm_t signature;
};
