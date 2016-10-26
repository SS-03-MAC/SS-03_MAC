//===-- EduTLS/src/tls/api/server.h                       -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file creates the TLS
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../states/Sessions.h"

class tls_server {
private:
  Sessions *sessions;

public:
  tls_server();
  ~tls_server();

  Sessions *Accept();
  SetConfiguration(char *option, );

};
