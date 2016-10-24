//===-- EduTLS/src/tls/enums/HashAlgorithm.h              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Hash Algorithm protocol.
///
//===----------------------------------------------------------------------===//

#pragma once


enum {
          none=0, md5=1, sha1=2, sha224=3, sha256=4, sha384=5,
          sha512=6, unknown=255
      } HashAlgorithm_t;
