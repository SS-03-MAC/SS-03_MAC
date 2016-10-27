//===-- EduTLS/src/tls/enums/ConnectionStates.h           -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Connection States protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./CompressionMethod.h"

enum class ConnectionEnd_e { server, client };
enum class PRFAlgorithm_e { tls_prf_sha256 };
enum class BulkCipherAlgorithm_e { null, rc4_128, des3_ede_cbc, aes_128_cbc, aes_256_cbc };
enum class CipherType_e { stream, block, aead };
enum class MACAlgorithm_e { null, hmac_md5, hmac_sha1, hmac_sha256, hmac_sha384, hmac_sha512 };
