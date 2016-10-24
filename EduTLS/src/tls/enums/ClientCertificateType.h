//===-- EduTLS/src/tls/enums/ClientCertificateType.h      -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains enums for the Client Certificate Type protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

enum {
    rsa_sign=1, dss_sign=2, rsa_fixed_dh=3, dss_fixed_dh=4,
    rsa_ephemeral_dh_RESERVED=5, dss_ephemeral_dh_RESERVED=6,
    fortezza_dms_RESERVED=20, unknown=255
} ClientCertificateType_t;
