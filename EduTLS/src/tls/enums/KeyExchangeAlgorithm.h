//===-- EduTLS/src/tls/enums/KeyExchangeAlgorithm.h       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Key Exchange Algorithm protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

enum class KeyExchangeAlgorithm_e { null, dhe_dss, dhe_rsa, dh_anon, rsa, dh_dss, dh_rsa };
