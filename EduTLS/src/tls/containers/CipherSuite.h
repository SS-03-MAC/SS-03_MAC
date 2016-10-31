//===-- EduTLS/src/tls/containers/CipherSute.h            -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains message declaration for the Cipher Suite protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>
#include <cstdlib>

#include <map>
#include <string>

#include "../enums/ConnectionStates.h"
#include "../enums/KeyExchangeAlgorithm.h"

class CipherSuite {
private:
  std::map<uint16_t, std::string> names;
  std::map<std::string, uint16_t> ids;
  std::map<std::string, KeyExchangeAlgorithm_e> exchange;
  std::map<std::string, BulkCipherAlgorithm_e> bulk;
  std::map<std::string, MACAlgorithm_e> mac;

public:
  uint8_t big;
  uint8_t little;

  CipherSuite() {
    this->big = 0;
    this->little = 0;

    this->PopulateMaps();
  };

  CipherSuite(uint8_t big, uint8_t little) {
    this->big = big;
    this->little = little;

    this->PopulateMaps();
  };

  bool Equals(CipherSuite c) { return this->big == c.big && this->little == c.little; }

  static CipherSuite *FromUint8(uint8_t *data, size_t length) {
    CipherSuite *result = new CipherSuite[length / 2];

    size_t i = 0;
    for (i = 0; i < length; i += 2) {
      result[i / 2] = CipherSuite(data[i], data[i + 1]);
    }

    return result;
  };

  KeyExchangeAlgorithm_e KeyExchange() {
    std::string name = this->names.at((this->big << 8) | this->little);
    return this->exchange.at(name);
  }

  BulkCipherAlgorithm_e BulkCipherAlgorithm() {
    std::string name = this->names.at((this->big << 8) | this->little);
    return this->bulk.at(name);
  }

  MACAlgorithm_e MACAlgorithm() {
    std::string name = this->names.at((this->big << 8) | this->little);
    return this->mac.at(name);
  }

  std::string String() {
    std::string result;
    result += "{";
    result += std::to_string(this->big);
    result += " ";
    result += std::to_string(this->little);
    result += "}: ";
    try {
      result += this->names.at((this->big << 8) | this->little);
    } catch (std::out_of_range e) {
      result += "<unknown>";
    }
    return result;
  }

  void PopulateMaps() {
    this->names[0x0000] = "TLS_NULL_WITH_NULL_NULL";
    this->names[0x0001] = "TLS_RSA_WITH_NULL_MD5";
    this->names[0x0002] = "TLS_RSA_WITH_NULL_SHA";
    this->names[0x003B] = "TLS_RSA_WITH_NULL_SHA256";
    this->names[0x0004] = "TLS_RSA_WITH_RC4_128_MD5";
    this->names[0x0005] = "TLS_RSA_WITH_RC4_128_SHA";
    this->names[0x000A] = "TLS_RSA_WITH_3DES_EDE_CBC_SHA";
    this->names[0x002F] = "TLS_RSA_WITH_AES_128_CBC_SHA";
    this->names[0x0035] = "TLS_RSA_WITH_AES_256_CBC_SHA";
    this->names[0x003C] = "TLS_RSA_WITH_AES_128_CBC_SHA256";
    this->names[0x003D] = "TLS_RSA_WITH_AES_256_CBC_SHA256";
    this->names[0x000D] = "TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA";
    this->names[0x0010] = "TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA";
    this->names[0x0013] = "TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA";
    this->names[0x0016] = "TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA";
    this->names[0x0030] = "TLS_DH_DSS_WITH_AES_128_CBC_SHA";
    this->names[0x0031] = "TLS_DH_RSA_WITH_AES_128_CBC_SHA";
    this->names[0x0032] = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA";
    this->names[0x0033] = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA";
    this->names[0x0036] = "TLS_DH_DSS_WITH_AES_256_CBC_SHA";
    this->names[0x0037] = "TLS_DH_RSA_WITH_AES_256_CBC_SHA";
    this->names[0x0038] = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA";
    this->names[0x0039] = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA";
    this->names[0x003E] = "TLS_DH_DSS_WITH_AES_128_CBC_SHA256";
    this->names[0x003F] = "TLS_DH_RSA_WITH_AES_128_CBC_SHA256";
    this->names[0x0040] = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA256";
    this->names[0x0067] = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256";
    this->names[0x0068] = "TLS_DH_DSS_WITH_AES_256_CBC_SHA256";
    this->names[0x0069] = "TLS_DH_RSA_WITH_AES_256_CBC_SHA256";
    this->names[0x006A] = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA256";
    this->names[0x006B] = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256";
    this->names[0x0018] = "TLS_DH_anon_WITH_RC4_128_MD5";
    this->names[0x001B] = "TLS_DH_anon_WITH_3DES_EDE_CBC_SHA";
    this->names[0x0034] = "TLS_DH_anon_WITH_AES_128_CBC_SHA";
    this->names[0x003A] = "TLS_DH_anon_WITH_AES_256_CBC_SHA";
    this->names[0x006C] = "TLS_DH_anon_WITH_AES_128_CBC_SHA256";
    this->names[0x006D] = "TLS_DH_anon_WITH_AES_256_CBC_SHA256";

    this->ids["TLS_NULL_WITH_NULL_NULL"] = 0x0000;
    this->ids["TLS_RSA_WITH_NULL_MD5"] = 0x0001;
    this->ids["TLS_RSA_WITH_NULL_SHA"] = 0x0002;
    this->ids["TLS_RSA_WITH_NULL_SHA256"] = 0x003B;
    this->ids["TLS_RSA_WITH_RC4_128_MD5"] = 0x0004;
    this->ids["TLS_RSA_WITH_RC4_128_SHA"] = 0x0005;
    this->ids["TLS_RSA_WITH_3DES_EDE_CBC_SHA"] = 0x000A;
    this->ids["TLS_RSA_WITH_AES_128_CBC_SHA"] = 0x002F;
    this->ids["TLS_RSA_WITH_AES_256_CBC_SHA"] = 0x0035;
    this->ids["TLS_RSA_WITH_AES_128_CBC_SHA256"] = 0x003C;
    this->ids["TLS_RSA_WITH_AES_256_CBC_SHA256"] = 0x003D;
    this->ids["TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA"] = 0x000D;
    this->ids["TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA"] = 0x0010;
    this->ids["TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA"] = 0x0013;
    this->ids["TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA"] = 0x0016;
    this->ids["TLS_DH_DSS_WITH_AES_128_CBC_SHA"] = 0x0030;
    this->ids["TLS_DH_RSA_WITH_AES_128_CBC_SHA"] = 0x0031;
    this->ids["TLS_DHE_DSS_WITH_AES_128_CBC_SHA"] = 0x0032;
    this->ids["TLS_DHE_RSA_WITH_AES_128_CBC_SHA"] = 0x0033;
    this->ids["TLS_DH_DSS_WITH_AES_256_CBC_SHA"] = 0x0036;
    this->ids["TLS_DH_RSA_WITH_AES_256_CBC_SHA"] = 0x0037;
    this->ids["TLS_DHE_DSS_WITH_AES_256_CBC_SHA"] = 0x0038;
    this->ids["TLS_DHE_RSA_WITH_AES_256_CBC_SHA"] = 0x0039;
    this->ids["TLS_DH_DSS_WITH_AES_128_CBC_SHA256"] = 0x003E;
    this->ids["TLS_DH_RSA_WITH_AES_128_CBC_SHA256"] = 0x003F;
    this->ids["TLS_DHE_DSS_WITH_AES_128_CBC_SHA256"] = 0x0040;
    this->ids["TLS_DHE_RSA_WITH_AES_128_CBC_SHA256"] = 0x0067;
    this->ids["TLS_DH_DSS_WITH_AES_256_CBC_SHA256"] = 0x0068;
    this->ids["TLS_DH_RSA_WITH_AES_256_CBC_SHA256"] = 0x0069;
    this->ids["TLS_DHE_DSS_WITH_AES_256_CBC_SHA256"] = 0x006A;
    this->ids["TLS_DHE_RSA_WITH_AES_256_CBC_SHA256"] = 0x006B;
    this->ids["TLS_DH_anon_WITH_RC4_128_MD5"] = 0x0018;
    this->ids["TLS_DH_anon_WITH_3DES_EDE_CBC_SHA"] = 0x001B;
    this->ids["TLS_DH_anon_WITH_AES_128_CBC_SHA"] = 0x0034;
    this->ids["TLS_DH_anon_WITH_AES_256_CBC_SHA"] = 0x003A;
    this->ids["TLS_DH_anon_WITH_AES_128_CBC_SHA256"] = 0x006C;
    this->ids["TLS_DH_anon_WITH_AES_256_CBC_SHA256"] = 0x006D;

    this->exchange["TLS_NULL_WITH_NULL_NULL"] = KeyExchangeAlgorithm_e::null;
    this->exchange["TLS_RSA_WITH_NULL_MD5"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_NULL_SHA"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_NULL_SHA256"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_RC4_128_MD5"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_RC4_128_SHA"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_RSA_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::rsa;
    this->exchange["TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_dss;
    this->exchange["TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_rsa;
    this->exchange["TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_dss;
    this->exchange["TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_rsa;
    this->exchange["TLS_DH_anon_WITH_RC4_128_MD5"] = KeyExchangeAlgorithm_e::dh_anon;
    this->exchange["TLS_DH_anon_WITH_3DES_EDE_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_anon;
    this->exchange["TLS_DH_DSS_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_dss;
    this->exchange["TLS_DH_RSA_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_rsa;
    this->exchange["TLS_DHE_DSS_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_dss;
    this->exchange["TLS_DHE_RSA_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_rsa;
    this->exchange["TLS_DH_anon_WITH_AES_128_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_anon;
    this->exchange["TLS_DH_DSS_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_dss;
    this->exchange["TLS_DH_RSA_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_rsa;
    this->exchange["TLS_DHE_DSS_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_dss;
    this->exchange["TLS_DHE_RSA_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::dhe_rsa;
    this->exchange["TLS_DH_anon_WITH_AES_256_CBC_SHA"] = KeyExchangeAlgorithm_e::dh_anon;
    this->exchange["TLS_DH_DSS_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_dss;
    this->exchange["TLS_DH_RSA_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_rsa;
    this->exchange["TLS_DHE_DSS_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::dhe_dss;
    this->exchange["TLS_DHE_RSA_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::dhe_rsa;
    this->exchange["TLS_DH_anon_WITH_AES_128_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_anon;
    this->exchange["TLS_DH_DSS_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_dss;
    this->exchange["TLS_DH_RSA_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_rsa;
    this->exchange["TLS_DHE_DSS_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::dhe_dss;
    this->exchange["TLS_DHE_RSA_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::dhe_rsa;
    this->exchange["TLS_DH_anon_WITH_AES_256_CBC_SHA256"] = KeyExchangeAlgorithm_e::dh_anon;

    this->bulk["TLS_NULL_WITH_NULL_NULL"] = BulkCipherAlgorithm_e::null;
    this->bulk["TLS_RSA_WITH_NULL_MD5"] = BulkCipherAlgorithm_e::null;
    this->bulk["TLS_RSA_WITH_NULL_SHA"] = BulkCipherAlgorithm_e::null;
    this->bulk["TLS_RSA_WITH_NULL_SHA256"] = BulkCipherAlgorithm_e::null;
    this->bulk["TLS_RSA_WITH_RC4_128_MD5"] = BulkCipherAlgorithm_e::rc4_128;
    this->bulk["TLS_RSA_WITH_RC4_128_SHA"] = BulkCipherAlgorithm_e::rc4_128;
    this->bulk["TLS_RSA_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_RSA_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_RSA_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_RSA_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_RSA_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_DH_anon_WITH_RC4_128_MD5"] = BulkCipherAlgorithm_e::rc4_128;
    this->bulk["TLS_DH_anon_WITH_3DES_EDE_CBC_SHA"] = BulkCipherAlgorithm_e::des3_ede_cbc;
    this->bulk["TLS_DH_DSS_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_RSA_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DHE_DSS_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DHE_RSA_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_anon_WITH_AES_128_CBC_SHA"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_DSS_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_RSA_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DHE_DSS_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DHE_RSA_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_anon_WITH_AES_256_CBC_SHA"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_DSS_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_RSA_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DHE_DSS_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DHE_RSA_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_anon_WITH_AES_128_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_128_cbc;
    this->bulk["TLS_DH_DSS_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_RSA_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DHE_DSS_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DHE_RSA_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;
    this->bulk["TLS_DH_anon_WITH_AES_256_CBC_SHA256"] = BulkCipherAlgorithm_e::aes_256_cbc;

    this->mac["TLS_NULL_WITH_NULL_NULL"] = MACAlgorithm_e::null;
    this->mac["TLS_RSA_WITH_NULL_MD5"] = MACAlgorithm_e::hmac_md5;
    this->mac["TLS_RSA_WITH_NULL_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_RSA_WITH_NULL_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_RSA_WITH_RC4_128_MD5"] = MACAlgorithm_e::hmac_md5;
    this->mac["TLS_RSA_WITH_RC4_128_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_RSA_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_RSA_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_RSA_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_RSA_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_RSA_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_anon_WITH_RC4_128_MD5"] = MACAlgorithm_e::hmac_md5;
    this->mac["TLS_DH_anon_WITH_3DES_EDE_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_DSS_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_RSA_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_DSS_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_RSA_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_anon_WITH_AES_128_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_DSS_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_RSA_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_DSS_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DHE_RSA_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_anon_WITH_AES_256_CBC_SHA"] = MACAlgorithm_e::hmac_sha1;
    this->mac["TLS_DH_DSS_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_RSA_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DHE_DSS_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DHE_RSA_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_anon_WITH_AES_128_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_DSS_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_RSA_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DHE_DSS_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DHE_RSA_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
    this->mac["TLS_DH_anon_WITH_AES_256_CBC_SHA256"] = MACAlgorithm_e::hmac_sha256;
  }
};
