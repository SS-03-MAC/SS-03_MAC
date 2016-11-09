#pragma once

#include <string>
#include <unistd.h>
#include <sys/stat.h>
namespace httpServer {

enum filesystemObject_t {
  file,
  folder,
  nonexistent
};

class filesystemUtils {
public:
  /**
   * Finds the type of an "object" on the filesystem if it exists.
   * @param path The path to the filessytem object.
   * @return path, file, or nonexistent (returned on any failure)
   */
  static filesystemObject_t info(std::string path);
  /**
   * Gets the file size of a file by its path.
   * @param path The path to the file.
   * @return The file size, or -1 on failure.
   */
  static ssize_t fileSize(std::string path);
};
}