//===-- eHTTP/utils/filesystem.h --------------------------------*- C++ -*-===//
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

#pragma once

#include <string>

namespace eHTTP {
namespace utils {

/// Represents an object on a filesystem.
enum filesystemObject_t {
  file,
  folder,
  nonexistent
};

class filesystem {
public:
  /// Finds the type of an "object" on the filesystem if it exists.
  /// \param path is the path to the filessytem object.
  /// \returns path, file, or nonexistent (returned on any failure)
  static filesystemObject_t info(std::string path);
  /// Gets the file size of a file by its path.
  /// \param path is the path to the file.
  /// \returns the file size, or -1 on failure.
  static ssize_t fileSize(std::string path);
};

}
}