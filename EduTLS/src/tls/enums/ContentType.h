//===-- EduTLS/src/tls/enums/ContentType.h                -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Content Type protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

enum class ContentType_t { change_cipher_spec = 20, alert = 21, handshake = 22, application_data = 23, max = 255 };
