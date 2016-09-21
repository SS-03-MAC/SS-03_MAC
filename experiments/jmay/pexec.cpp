//
// Created by JoelM on 2016-09-20.
//

#include <unistd.h>
#include <cstdlib>
#include "pexec.h"

// 0 - read, 1 - write, 2 read_err
int pexec(const char *file_name, int pipefd[3], char **argv, char **envp) {
  pid_t fork_status;
  int pipe_to_child[2];
  int pipe_from_child[2];
  int pipe_err_from_child[2];
  if(pipe(pipe_to_child) || pipe(pipe_from_child) || pipe(pipe_err_from_child)) {
    // Pipe failed
    return -1;
  }

  fork_status = fork();
  if(fork_status == -1) {
    // Fork failed
    return -1;
  }
  if(fork_status != 0) {
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

    environ = envp;
    execvp(file_name, argv);
    // execvp never returns on success, end this thread
    close(pipe_to_child[0]);
    close(pipe_from_child[1]);
    close(pipe_err_from_child[1]);
    exit(-1);
  }
}