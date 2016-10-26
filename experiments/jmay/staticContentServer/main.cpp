#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <ext/stdio_filebuf.h>
#include "network/TcpServer.h"
#include "httpParsing/httpRequestHeaderCollection.h"
#include "httpParsing/httpResponseHeaderCollection.h"

void forkClient(int clientFd);
void handleClient(int clientFd);
std::ifstream *getFile(std::string &path);
long getFileSize(std::string &path);

std::string basePath;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char *argv[]) {
  if (argc > 1) {
    basePath = argv[1];
  } else {
    basePath = "c:";
  }

  int tcp = network::tcp_start();
  int client;
  while (true) {
    client = network::tcp_accept(tcp);
    forkClient(client);
  }
}
#pragma clang diagnostic pop

void forkClient(int clientFd) {
  int child = fork();
  if (child == -1) {
    std::cout << "Forking a handling thread failed" << std::endl;
  } else if (child == 0) {
    handleClient(clientFd);
    exit(0);
  }
}

void handleClient(int clientFd) {
  __gnu_cxx::stdio_filebuf<char> filebuf(clientFd, std::ios::in);
  std::istream clientStream(&filebuf);
  httpRequestHeaderCollection *headers;
  try {
    headers = new httpRequestHeaderCollection(&clientStream);
  } catch (const char *err) {
    std::cout << "Error handling request: " << err << std::endl;
    shutdown(clientFd, SHUT_RDWR);
    return;
  }
  std::cout << "Request: " << headers->toString() << std::endl;

  std::ifstream *fileStream = getFile(headers->path); //new std::ifstream("c:\\test.txt", std::ifstream::in);

  if (fileStream->fail()) {
    std::cout << "Error opening file" << std::endl;
    httpResponseHeaderCollection resp("HTTP/1.1", 404, "Not Found");
    std::string errorText(resp.toString());
    errorText += "Error opening file";
    write(clientFd, errorText.c_str(), errorText.length());
  } else {
    httpResponseHeaderCollection resp("HTTP/1.1", 200, "Success");
    
    resp.push_back(new httpHeader("Content-Length", std::to_string(getFileSize(headers->path))));

    std::string headerString(resp.toString());
    write(clientFd, headerString.c_str(), headerString.length());
    network::write_stream(clientFd, *fileStream);
  }
  fileStream->close();
  shutdown(clientFd, SHUT_RDWR);
}

std::ifstream *getFile(std::string &path) {
  std::string processedPath(basePath);
  if (path == "/") {
    processedPath += "/index.html";
  } else {
    processedPath += path;
  }
  return new std::ifstream(processedPath, std::ifstream::in);
}

long getFileSize(std::string &path) {
  std::string processedPath(basePath);
  if (path == "/") {
    processedPath += "/index.html";
  } else {
    processedPath += path;
  }
  std::ifstream in(processedPath, std::ios::ate | std::ios::binary);
  return in.tellg();
}