//===--EduTLS/src/tls/abstractions/ServerStream.h         -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the ServerStream class declaration..
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <streambuf>

#include <iosfwd>

#include "../../crypto/crypto.h"
#include "../../encoding/encoding.h"
#include "../tls.h"

class TLSServerStreamBuf : public std::streambuf {
private:
  TLSServer *s;

  uint8_t inbuf[65536];
  uint8_t outbuf[65536];

  size_t i_p;
  size_t i_l;
  size_t o_p;
  size_t o_l;

public:
  TLSServerStreamBuf(TLSServer *s) {
    this->s = s;
    this->i_p = 0;
    this->i_l = 0;
    this->o_p = 0;
    this->o_l = 65536;
  };

  int_type underflow() {
    if (this->i_p == this->i_l) {
      if (this->s->IsClosed()) {
        return EOF;
      }

      this->i_l = this->s->Read(this->inbuf);
      this->i_p = 0;

      if (this->i_p == this->i_l) {
        return EOF;
      }
    }

    return this->inbuf[this->i_p];
  };

  int uflow() {
    if (underflow() == EOF) {
      return EOF;
    }

    return this->inbuf[this->i_p++];
  }

  int_type sputbackc(int_type c) {
    if (this->i_p != 0) {
      if (this->inbuf[this->i_p - 1] != c) {
        return EOF;
      }
      this->i_p -= 1;
      return c;
    } else {
      return EOF;
    }
  }

  int_type overflow(int_type ch) {
    if (ch == traits_type::eof()) {
      this->s->Write(this->outbuf, this->o_p);
      this->o_p = 0;

      return traits_type::eof();
    }

    if (this->o_p == this->o_l) {
      this->s->Write(this->outbuf, this->o_p);
      this->o_p = 0;
    }

    this->outbuf[this->o_p++] = (uint8_t)ch;
    return (uint8_t)ch;
  };

  int sync() {
    this->s->Write(this->outbuf, this->o_p);
    this->o_p = 0;

    return 0;
  };

  int pbackfail(int c) {
    return sputbackc(c);
    // return EOF;
  }
};

class TLSServerStream : public std::iostream {
public:
  TLSServerStream(TLSServer *s) : std::iostream(new TLSServerStreamBuf(s)){};

  ~TLSServerStream(){};
};
