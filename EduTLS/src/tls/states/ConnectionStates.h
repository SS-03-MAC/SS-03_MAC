//===-- EduTLS/src/tls/states/ConnectionStates.h          -------*- C++ -*-===//
//
//                     EduTLS - Transport Layer Security
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains state objects for the Connection States protocol.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "./SecurityParameters.h"

class ConnectionStates {
public:
  SecurityParameters *current_read;
  SecurityParameters *current_write;
  SecurityParameters *pending_read;
  SecurityParameters *pending_write;
};
