//===-- EduTLS/src/encoding/constants/asn1.h              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains constants for the ASN.1 Abstract Syntax Notation One
/// universal class types as defined in ITU-T X.680.
///
//===----------------------------------------------------------------------===//

#pragma once

#define ASN_BOOLEAN_CLASS 0x01;
#define ASN_INTEGER_CLASS 0x02;
#define ASN_BIT_STRING_CLASS 0x03;
#define ASN_OCTET_STRING_CLASS 0x04;
#define ASN_NULL_CLASS 0x05;
#define ASN_REAL_CLASS 0x09;
#define ASN_ENUMERATED_CLASS 0x0A;
#define ASN_SEQUENCE_CLASS 0x10;
#define ASN_SEQUENCE_OF_TYPES_CLASS 0x10;
#define ASN_SET_CLASS 0x11;
#define ASN_SET_OF_TYPE_CLASS 0x11;
#define ASN_OBJECT_IDENTIFIER_CLASS 0x06;
#define ASN_RELATIVE_OBJECT_IDENTIFIER_CLASS 0x0D;
#define ASN_EMBEDDED_PDV_CLASS 0xB;
#define ASN_EXTERNAL_TYPE_CLASS 0x08;
#define ASN_UNRESTRICTED_CHARACTER_STRING_CLASS 0x1D;
