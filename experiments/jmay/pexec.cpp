//
// Created by JoelM on 2016-09-20.
//

#include <unistd.h>
#include "pexec.h"

int pexec(const char *file_name, int pipefd[2]) {
  int pipe_to_child[2];
  int pipe_from_child[2];
  if(pipe(pipe_to_child)) {
    // Pipe failed
    return -1;
  }
  if(pipe(pipe_from_child)) {
    // Pipe failed
    return -1;
  }
  // fork
  //  both - close old pipes
  //  child - connect pipes
  // close pipes
}