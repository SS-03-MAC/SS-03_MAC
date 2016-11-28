//===-- eHTTP/pexec/pexec.h -------------------------------------*- C++ -*-===//
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

#pragma once

/// Forks \p file_name (by searching the PATH environment variable).  Hooks stdio to \p pipefd with
/// pipefd[0] -> stdout,
/// pipefd[1] -> stdin,
/// pipefd[2] -> stderr
/// \param argv is the NULL-terminated argument vector for the executed process, excluding the process itself.
/// \param envp is the NULL-terminated environment pointer.  The current PATH will be added to it.
int pexec(const char *file_name, int pipefd[3], char **argv, char **envp);
