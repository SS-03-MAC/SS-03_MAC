//===-- EduTLS/src/tls/tls.h                              -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file includes everything needed for TLS v1.2
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./containers/GenericAEADCipher.h"
#include "./containers/GenericBlockCipher.h"
#include "./containers/GenericStreamCipher.h"
#include "./containers/TLSCiphertext.h"
#include "./containers/TLSCompressed.h"
#include "./containers/TLSPlaintext.h"
#include "./enums/Alert.h"
#include "./enums/ChangeCipherSpec.h"
#include "./enums/ClientCertificateType.h"
#include "./enums/CompressionMethod.h"
#include "./enums/ConnectionStates.h"
#include "./enums/ContentType.h"
#include "./enums/ExtensionType.h"
#include "./enums/HandshakeType.h"
#include "./enums/HashAlgorithm.h"
#include "./enums/KeyExchangeAlgorithm.h"
#include "./enums/SignatureAlgorithm.h"
#include "./interfaces/encodable.h"
#include "./messages/Alert.h"
#include "./messages/Certificate.h"
#include "./messages/CertificateRequest.h"
#include "./messages/ChangeCipherSpec.h"
#include "./messages/ClientHello.h"
#include "./messages/DigitallySigned.h"
#include "./messages/Extension.h"
#include "./messages/Handshake.h"
#include "./messages/HelloRequest.h"
#include "./messages/ProtocolVersion.h"
#include "./messages/Random.h"
#include "./messages/ServerDHParams.h"
#include "./messages/ServerHello.h"
#include "./messages/ServerHelloDone.h"
#include "./messages/ServerKeyExchange.h"
#include "./messages/SignatureHashAlgorithm.h"
#include "./states/ConnectionStates.h"
#include "./states/SecurityParameters.h"
