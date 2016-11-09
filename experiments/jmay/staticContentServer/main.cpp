#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <ext/stdio_filebuf.h>
#include "network/TcpServer.h"
#include "httpParsing/httpRequestHeaderCollection.h"
#include "httpParsing/httpResponseHeaderCollection.h"
#include "serverSettings.h"
#include "filesystemUtils.h"

void forkClient(int clientFd);
void handleClient(int clientFd);
int serveFile(int clientFd, httpParsing::AbsPath &path);
bool getFileFromPath(httpParsing::AbsPath &path, std::string &outFile);
void redirectClient(int clientFd, std::string path);

httpServer::settings serverSettings;
//std::string basePath;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char *argv[]) {
  if (argc > 1) {
    serverSettings.basePath = argv[1];
  } else {
    serverSettings.basePath = "c:";
  }
  serverSettings.port = 8000;
  serverSettings.defaultDocuments.push_back("test2.txt");
  serverSettings.defaultDocuments.push_back("index.html");
  struct httpServer::cgiEndpoint_t ep1;
  ep1.pathElement = "api";
  ep1.cgiPath = "dir";
  serverSettings.cgiEndpoints.push_back(ep1);

  int tcp = network::tcp_start(serverSettings.port);
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

  serveFile(clientFd, *headers->path);

  shutdown(clientFd, SHUT_RDWR);
}

int serveFile(int clientFd, httpParsing::AbsPath &path) {
  std::string fileToServe;
  bool fileExists = getFileFromPath(path, fileToServe);
  std::ifstream *fileStream = new std::ifstream(fileToServe, std::ifstream::in); //new std::ifstream("c:\\test.txt", std::ifstream::in);

  if (!fileExists || fileStream->fail()) {
    std::cout << "Error opening file" << std::endl;
    httpResponseHeaderCollection resp("HTTP/1.1", 404, "Not Found");
    std::string errorText(resp.toString());
    errorText += "Error opening file";
    write(clientFd, errorText.c_str(), errorText.length());
    return 1;
  } else {
    httpResponseHeaderCollection resp("HTTP/1.1", 200, "Success");

    ssize_t fileSize = httpServer::filesystemUtils::fileSize(fileToServe);
    resp.push_back(new httpHeader("Content-Length", std::to_string(fileSize)));

    std::string headerString(resp.toString());
    write(clientFd, headerString.c_str(), headerString.length());
    network::write_stream(clientFd, *fileStream);
  }
  fileStream->close();
  return 0;
}

bool getFileFromPath(httpParsing::AbsPath &path, std::string &outFile) {
  //Is it a folder
  // - Does the path end in a slash
  // - Is the path a folder
  //If folder
  // - Append defualtDocuments
  // - Is new path a file
  std::string fullPath = serverSettings.basePath + "/" + path.getFullPath();
  std::string fileToServe;
  std::cout << "file to serve before processing: " << fullPath << std::endl;
  std::cout << "ends in slash: " << path.endsInSlash() << std::endl;
  bool folder = false;
  if (path.endsInSlash()) {
    folder = true;
  } else {
    httpServer::filesystemObject_t fInfo = httpServer::filesystemUtils::info(fullPath);
    switch (fInfo) {
    case httpServer::filesystemObject_t::folder:
      //TODO redirect the client to "<path>/"
      return false;
    case httpServer::filesystemObject_t::nonexistent:
      return false;
    default:break;
    }
  }
  if (folder) {
    bool isFile = false;
    for (int i = 0; !isFile && i < serverSettings.defaultDocuments.size(); i++) {
      fileToServe = fullPath + serverSettings.defaultDocuments[i];
      std::cout << "searching for: " << fileToServe << std::endl;
      isFile = httpServer::filesystemUtils::info(fileToServe) == httpServer::filesystemObject_t::file;
    }
    if (!isFile) {
      return false;
    }
  } else {
    fileToServe = fullPath;
  }
  std::cout << "trying to serve " << fileToServe << std::endl;
  outFile = fileToServe;
  return true;
}
