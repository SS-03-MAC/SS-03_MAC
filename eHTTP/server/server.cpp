
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <ext/stdio_filebuf.h>
#include <sys/socket.h>
#include <cstring>
#include <algorithm>

#include "server.h"
#include "../utils/filesystem.h"
#include "../pexec/pexec.h"
#include "../network/TcpServer.h"
#include "../httpParsing/httpResponseHeaderCollection.h"
#include "../EduTLS/src/tls/api/TLSServer.h"
#include "../../EduTLS/src/tls/abstractions/ServerStream.h"

using namespace eHTTP::server;

// ===== CONSTRUCTORS =====

server::server(uint16_t port, std::string basePath) {
  createdSettings = true;
  settings = new eHTTP::server::settings;
  settings->basePath = basePath;
  settings->defaultDocuments.push_back("index.html");
  settings->port = port;
}

server::server(eHTTP::server::settings &settings, TLSConfiguration &TlsConfig) {
  this->settings = &settings;
  this->tlsConfig = &TlsConfig;
}

server::~server() {
  if (createdSettings) {
    delete settings;
  }
}

void server::forkHandler(int clientFd, void (eHTTP::server::server:: *handler)(int)) {
  /*int child = fork();
  if (child == -1) {
    std::cout << "Forking a handling thread failed" << std::endl;
  } else if (child == 0) {*/
    (this->*handler)(clientFd);
    /*exit(0);
  }*/
}

// ===== FUNCTIONS =====

void server::handleClient(int clientFd) {
  __gnu_cxx::stdio_filebuf<char> filebuf(clientFd, std::ios::in);
  std::istream clientStream(&filebuf);
  httpRequestHeaderCollection *headers;
  eHTTP::server::cgiEndpoint_t cgiEndpoint;
  try {
    headers = new httpRequestHeaderCollection(&clientStream);
  } catch (const char *err) {
    std::cout << "Error handling request: " << err << std::endl;
    shutdown(clientFd, SHUT_RDWR);
    return;
  }
  std::cout << "Request: " << headers->toString() << std::endl;

  if (settings->getScriptForPath(*headers->path, cgiEndpoint)) {
    std::cout << "Serving via CGI: " << headers->path->getPathAndQueryString() << std::endl;
    serveCgi(clientStream, (void *) &clientFd, *headers->path, cgiEndpoint, *headers, false);
  } else {
    std::cout << "Serving static file" << std::endl;
    serveFile(clientFd, *headers->path);
  }

  shutdown(clientFd, SHUT_RDWR);
}

void server::handleClientTls(int clientFd) {
  TLSServer *srv = new TLSServer(tlsConfig);
  srv->AcceptClient(clientFd);
  srv->Handshake();
  TLSServerStream *clientStream = new TLSServerStream(srv);

  httpRequestHeaderCollection *headers;
  eHTTP::server::cgiEndpoint_t cgiEndpoint;
  try {
    headers = new httpRequestHeaderCollection(clientStream);
  } catch (const char *err) {
    std::cout << "Error handling request: " << err << std::endl;
    shutdown(clientFd, SHUT_RDWR);
    return;
  }
  std::cout << "Request: " << headers->toString() << std::endl;

  if (settings->getScriptForPath(*headers->path, cgiEndpoint)) {
    std::cout << "Serving via CGI: " << headers->path->getPathAndQueryString() << std::endl;
    serveCgi(*clientStream, (void *) srv, *headers->path, cgiEndpoint, *headers, true);
  } else {
    std::cout << "Serving static file" << std::endl;
    serveFileTls(*srv, *headers->path);
  }

  srv->Close();
  delete clientStream;
  delete srv;
}

long long server::serveFile(int clientFd, httpParsing::AbsPath &path) {
  std::string fileToServe;
  bool fileExists = getFileFromPath(path, fileToServe);
  std::ifstream *fileStream = new std::ifstream(fileToServe, std::ifstream::in);
  long long dataTransmitted;

  if (!fileExists || fileStream->fail()) {
    std::cout << "Error opening file: " << fileToServe << std::endl;
    httpResponseHeaderCollection resp("HTTP/1.1", 404, "Not Found");
    std::string errorText(resp.toString());
    errorText += "Error opening file";
    write(clientFd, errorText.c_str(), errorText.length());
    return -1;
  } else {
    httpResponseHeaderCollection resp("HTTP/1.1", 200, "Success");

    ssize_t fileSize = eHTTP::utils::filesystem::fileSize(fileToServe);
    resp.push_back(new httpHeader("Content-Length", std::to_string(fileSize)));

    std::string headerString(resp.toString());
    write(clientFd, headerString.c_str(), headerString.length());
    dataTransmitted = network::write_stream(clientFd, *fileStream);
  }
  fileStream->close();
  delete fileStream;
  return dataTransmitted;
}

long long server::serveFileTls(TLSServer &client, httpParsing::AbsPath &path) {
  std::string fileToServe;
  bool fileExists = getFileFromPath(path, fileToServe);
  std::ifstream *fileStream = new std::ifstream(fileToServe, std::ifstream::in);
  long long dataTransmitted;

  if (!fileExists || fileStream->fail()) {
    std::cout << "Error opening file: " << fileToServe << std::endl;
    httpResponseHeaderCollection resp("HTTP/1.1", 404, "Not Found");
    std::string errorText(resp.toString());
    errorText += "Error opening file";
    client.Write((uint8_t *) errorText.c_str(), errorText.length());
    return -1;
  } else {
    httpResponseHeaderCollection resp("HTTP/1.1", 200, "Success");

    ssize_t fileSize = eHTTP::utils::filesystem::fileSize(fileToServe);
    resp.push_back(new httpHeader("Content-Length", std::to_string(fileSize)));

    std::string headerString(resp.toString());
    client.Write((uint8_t *) headerString.c_str(), headerString.length());
    dataTransmitted = network::write_stream_tls(client, *fileStream);
  }
  fileStream->close();
  delete fileStream;
  return dataTransmitted;
}

long long server::serveCgi(std::istream &tcpIstream,
                           void *client,
                           httpParsing::AbsPath &path,
                           eHTTP::server::cgiEndpoint_t cgiEndpoint,
                           httpRequestHeaderCollection &requestHeaders,
                           bool tls) {
  int cgiPipes[3];
  ssize_t requestContentLen = 0;
  // TODO use CGI arguments as NULL terminated vector.
  char *argv[] = {(char *) cgiEndpoint.cgiPath.c_str(), NULL, NULL};
  if (cgiEndpoint.cgiArguments.length() > 0) {
    argv[1] = (char *) cgiEndpoint.cgiArguments.c_str();
  }
  if (requestHeaders.keyExists("Content-Length")) {
    requestContentLen = (ssize_t) requestHeaders.getInt64Value("Content-Length");
  }
  std::cout << "Request content length: " << requestContentLen << std::endl;

  // CGI out
  char **env = headersToEnvArray(requestHeaders);
  std::cout << "env 0: " << env[0] << std::endl;
  pexec(cgiEndpoint.cgiPath.c_str(), cgiPipes, argv, env);
  freeEnvArray(env);
  if (tls) {
    return network::passDataTls(tcpIstream, (TLSServer *) client, cgiPipes[0], cgiPipes[1], requestContentLen, 1024);
  } else {
    return network::passData(tcpIstream, (int *) client, cgiPipes[0], cgiPipes[1], requestContentLen, 1024);
  }
}

bool server::getFileFromPath(httpParsing::AbsPath &path, std::string &outFile) {
  // Is it a folder
  //  - Does the path end in a slash
  //  - Is the path a folder
  // If folder
  //  - Foreach defaultDocuments -> append
  //  - Is new path a file
  std::string fullPath = settings->basePath + "/" + path.getFullPath();
  std::string fileToServe;
  bool folder = false;
  if (path.endsInSlash()) {
    folder = true;
  } else {
    eHTTP::utils::filesystemObject_t fInfo = eHTTP::utils::filesystem::info(fullPath);
    switch (fInfo) {
    case eHTTP::utils::filesystemObject_t::folder:
      // TODO redirect the client to "<path>/"
      return false;
    case eHTTP::utils::filesystemObject_t::nonexistent: return false;
    default: break;
    }
  }
  if (folder) {
    bool isFile = false;
    for (int i = 0; !isFile && i < settings->defaultDocuments.size(); i++) {
      fileToServe = fullPath + settings->defaultDocuments[i];
      std::cout << "Searching for: " << fileToServe << std::endl;
      isFile = eHTTP::utils::filesystem::info(fileToServe) == eHTTP::utils::filesystemObject_t::file;
    }
    if (!isFile) {
      return false;
    }
  } else {
    fileToServe = fullPath;
  }
  outFile = fileToServe;
  return true;
}

char** server::headersToEnvArray(httpRequestHeaderCollection &headers) {
  // Set up environment
  char **env = (char **) malloc(sizeof(char *) * (3 + headers.size()));
  int i;
  std::string temp;

  for (i = 0; i < headers.size(); i++) {
    temp = headers[i]->key;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    temp += "=";
    temp += headers[i]->value;
    env[i] = (char *) malloc(sizeof(char) * (temp.length() + 1));
    strcpy(env[i], temp.c_str());
  }

  //TODO more headers such as HTTP version?

  temp = "REQUEST_METHOD=";
  temp += headers.getVerb();
  env[i] = (char *) malloc(temp.length() + 1);
  strcpy(env[i++], temp.c_str());

  temp = "SCRIPT_PATH=";
  temp += headers.path->getScriptPath();
  env[i] = (char *) malloc(temp.length() + 1);
  strcpy(env[i++], temp.c_str());

  env[i] = NULL;
  return env;
}

void server::freeEnvArray(char **env) {
  int i = 0;
  //TODO why does this not work?  i gets changed.
  /*while (env[i] != NULL) {
    free(env[i]);
    i++;
  }
  free(env);*/
}

void server::addCgiEndpoint(std::string pathElement, std::string cgiPath, std::string cgiArguments) {
  eHTTP::server::cgiEndpoint_t newEP;
  newEP.pathElement = pathElement;
  newEP.cgiPath = cgiPath;
  newEP.cgiArguments = cgiArguments;
  settings->cgiEndpoints.push_back(newEP);
}

void server::addDefaultDocument(std::string document) {
  settings->defaultDocuments.push_back(document);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void server::serve() {
  // TODO listen on TLS port too
  int tcp = network::tcp_start(settings->port);
  int client;
  while (true) {
    client = network::tcp_accept(tcp);
    forkHandler(client, &eHTTP::server::server::handleClientTls);
  }
}
#pragma clang diagnostic pop
