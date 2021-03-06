//===-- eHTTP/pexec/pexec.cpp -----------------------------------*- C++ -*-===//
//
//                     eHTTP - Web Server with CGI
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a method for forking a program and hooking to its stdio.
///
//===----------------------------------------------------------------------===//

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <errno.h>

#include "pexec.h"

/// Copies the values from envp to the environment.  Preserves PATH.
/// \param envp NULL terminated array of environment variables
void setEnviron(char **envp);

// 0 - read, 1 - write, 2 read_err
int pexec(const char *file_name, int pipefd[3], char **argv, char **envp) {
  // TODO this method is too large.  It should be broken into smaller functions.
  pid_t fork_status;
  int pipe_to_child[2];
  int pipe_from_child[2];
  int pipe_err_from_child[2];
  if (pipe(pipe_to_child) || pipe(pipe_from_child) || pipe(pipe_err_from_child)) {
    // Pipe failed
    return -1;
  }

  fork_status = fork();
  if (fork_status == -1) {
    // Fork failed
    std::cout << "Fork failed in pexec. errno: " << errno << std::endl;
    return -1;
  }
  if (fork_status != 0) {
    // Parent
    close(pipe_to_child[0]);
    close(pipe_from_child[1]);
    close(pipe_err_from_child[1]);
    pipefd[0] = pipe_from_child[0];
    pipefd[1] = pipe_to_child[1];
    pipefd[2] = pipe_err_from_child[0];
    return 0;
  } else {
    // Child
    close(pipe_to_child[1]);
    close(pipe_from_child[0]);
    close(pipe_err_from_child[0]);
    dup2(pipe_from_child[1], STDOUT_FILENO);
    dup2(pipe_to_child[0], STDIN_FILENO);
    dup2(pipe_err_from_child[1], STDERR_FILENO);

    setEnviron(envp);
    execvp(file_name, argv);
    std::cout << "Error executing CGI script, errno: " << errno << std::endl;
    // execvp never returns on success, end this thread
    close(pipe_to_child[0]);
    close(pipe_from_child[1]);
    close(pipe_err_from_child[1]);
    exit(-1);
  }
}

void setEnviron(char **envp) {
  char **newEnv;
  std::string path = "PATH=";
  path += getenv("PATH");
  // Count before copy
  unsigned int count = 0;
  while (envp[count++] != NULL)
    ;

  // Allocate memory (+1 for the PATH)
  newEnv = (char **) malloc((count + 1) * sizeof(char *));
  // Copy data
  int i;
  for (i = 0; i < count - 1; i++) {
    newEnv[i] = envp[i];
  }
  newEnv[i] = (char *) malloc(path.length() + 1);
  strcpy(newEnv[i], path.c_str());
  i++;
  newEnv[i] = NULL;

  environ = newEnv;
}
