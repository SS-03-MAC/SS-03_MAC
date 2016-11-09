#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <ext/stdio_filebuf.h>
#include <map>
#include "pexec/pexec.h"
#include "network/TcpServer.h"
#include "httpParsing/httpRequestHeaderCollection.h"
#include "httpParsing/httpResponseHeaderCollection.h"
#include "serverSettings.h"
#include "filesystemUtils.h"

void forkClient(int clientFd);
void handleClient(int clientFd);
int serveFile(int clientFd, httpParsing::AbsPath &path);
int serveCGI(std::istream &tcpistream,
             int clientFd,
             httpParsing::AbsPath &path,
             httpServer::cgiEndpoint_t cgiEndpoint,
             httpRequestHeaderCollection &requestHeaders);
bool getFileFromPath(httpParsing::AbsPath &path, std::string &outFile);
void redirectClient(int clientFd, std::string path);
ssize_t passData(std::istream &tcpisteram,
                 int *cgiPipes,
                 int clientFd,
                 size_t requestContentLen,
                 uint8_t *buf,
                 int bufSize);

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
  struct httpServer::cgiEndpoint_t ep2;
  ep1.pathElement = "api";
  ep1.cgiPath = "echo";
  ep1.cgiArguments = "hi";
  ep2.pathElement = "env";
  ep2.cgiPath = "printenv";
  serverSettings.cgiEndpoints.push_back(ep1);
  serverSettings.cgiEndpoints.push_back(ep2);

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
  httpServer::cgiEndpoint_t cgiEndpoint;
  try {
    headers = new httpRequestHeaderCollection(&clientStream);
  } catch (const char *err) {
    std::cout << "Error handling request: " << err << std::endl;
    shutdown(clientFd, SHUT_RDWR);
    return;
  }
  std::cout << "Request: " << headers->toString() << std::endl;

  if (serverSettings.getScriptForPath(*headers->path, cgiEndpoint)) {
    std::cout << "Serving via cgi" << std::endl;
    serveCGI(clientStream, clientFd, *headers->path, cgiEndpoint, *headers);
  } else {
    std::cout << "Serving static file" << std::endl;
    serveFile(clientFd, *headers->path);
  }

  shutdown(clientFd, SHUT_RDWR);
}

int serveFile(int clientFd, httpParsing::AbsPath &path) {
  std::string fileToServe;
  bool fileExists = getFileFromPath(path, fileToServe);
  std::ifstream *fileStream =
      new std::ifstream(fileToServe, std::ifstream::in); //new std::ifstream("c:\\test.txt", std::ifstream::in);

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

int serveCGI(std::istream &tcpistream,
             int clientFd,
             httpParsing::AbsPath &path,
             httpServer::cgiEndpoint_t cgiEndpoint,
             httpRequestHeaderCollection &requestHeaders) {
  uint8_t buf[10240];
  int cgiPipes[3];
  char *argv[] = {(char *) cgiEndpoint.cgiPath.c_str(), NULL, NULL};
  ssize_t sizeFromClient;
  size_t requestContentLen = 0;
  if (cgiEndpoint.cgiArguments.length() > 0) {
    argv[1] = (char *) cgiEndpoint.cgiArguments.c_str();
  }
  if (requestHeaders.keyExists("Content-Length")) {
    requestContentLen = (size_t) requestHeaders.getInt64Value("Content-Length");
  }
  std::cout << "Request content len" << requestContentLen << std::endl;

  // Set up environment
  char **env = (char **) malloc(3);
  std::string temp;
  temp = "REQUEST_METHOD=";
  temp += requestHeaders.getVerb();
  env[0] = (char *) malloc(temp.length());
  strcpy(env[0], temp.c_str());

  temp = "SCRIPT_PATH=";
  temp += requestHeaders.path->getScriptPath();
  env[1] = (char *) malloc(temp.length());
  strcpy(env[1], temp.c_str());
  env[2] = NULL;

  // cgi out
  pexec(cgiEndpoint.cgiPath.c_str(), cgiPipes, argv, env);
  sizeFromClient = passData(tcpistream, cgiPipes, clientFd, requestContentLen, buf, sizeof(buf));
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
    case httpServer::filesystemObject_t::nonexistent:return false;
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

/*void sendLine(int fd, char *str, ssize_t len) {
  char const *crlf = "\r\n";
  write(fd, str, len);
  write(fd, crlf, 2);
}*/

ssize_t passData(std::istream &tcpistream,
                 int *cgiPipes,
                 int clientFd,
                 size_t requestContentLen,
                 uint8_t *buf,
                 int bufSize) {
  ssize_t r;
  ssize_t bufPos = 0;
  // tcp in
  while (requestContentLen > 0) {
    tcpistream.read((char *) buf, requestContentLen);
    write(cgiPipes[1], buf, (size_t) tcpistream.gcount());
    requestContentLen -= tcpistream.gcount();
  }

  // cgi in
  r = read(cgiPipes[0], buf, bufSize - 1);
  do {
    // tcp out
    write(clientFd, buf + bufPos, r);
    bufPos += r;
    r = read(cgiPipes[0], buf + bufPos, bufSize - bufPos);
  } while (r > 0);
  return bufPos;
}
