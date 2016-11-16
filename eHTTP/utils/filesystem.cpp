//===-- eHTTP/utils/filesystem.cpp ------------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains utilities that are helpful for filesystem access.
///
//===----------------------------------------------------------------------===//

#include <unistd.h>
#include <sys/stat.h>

#include "filesystem.h"

using namespace eHTTP::utils;

filesystemObject_t filesystem::info(std::string path) {
  if (access(path.c_str(), F_OK) == 0) {
    // File or folder exists
    struct stat status;
    if (stat(path.c_str(), &status) == -1) {
      return nonexistent;
    }
    if (status.st_mode & S_IFDIR) {
      return folder;
    } else {
      return file;
    }
  } else {
    return nonexistent;
  }
}

ssize_t filesystem::fileSize(std::string path) {
  struct stat status;
  if (stat(path.c_str(), &status) == -1) {
    return -1;
  }
  return status.st_size;
}