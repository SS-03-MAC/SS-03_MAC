//
// Created by JoelM on 2016-09-22.
//

#include <unistd.h>
#include <iostream>
#include "../pexec.h"

int main(int argc, char *argv[]) {
  int pipes[3];
  char buffer[5000];
  ssize_t size;
  char *e[1000];
  int i = 0;
  do {
    e[i] = environ[i];
  } while (i++ < 18);
  std::cout << "e[16] == " << e[17] << std::endl;
  e[17] = NULL;
  char *args[3];
  args[0] = (char *) "env";
  args[1] = NULL;
  environ[0] = (char *) "whatwhat";
  std::cout << "pexec: " << pexec("env", pipes, args, e) << std::endl;
  size = read(pipes[0], buffer, sizeof(buffer));
  buffer[size] = '\0';
  std::cout << "Child said: " << buffer << std::endl;
  std::cout << size << " bytes" << std::endl;
  close(pipes[0]);
  close(pipes[1]);
  close(pipes[2]);
  return 0;
}