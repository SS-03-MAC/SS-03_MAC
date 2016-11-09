#include <iostream>
#include "filesystemUtils.h"
using namespace httpServer;

filesystemObject_t filesystemUtils::info(std::string path) {
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

ssize_t filesystemUtils::fileSize(std::string path) {
  struct stat status;
  if (stat(path.c_str(), &status) == -1) {
    return -1;
  }
  return status.st_size;
}