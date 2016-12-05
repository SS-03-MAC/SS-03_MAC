#pragma once

#include <functional>
#include "../../EduTLS/src/tls/states/TLSConfiguration.h"
#include "settings.h"
#include "../httpParsing/httpRequestHeaderCollection.h"
#include "../../EduTLS/src/tls/api/TLSServer.h"

namespace eHTTP {
namespace server {

class server {
private:
  /// Keeps track of what needs to be deleted in the destructor.
  bool createdSettings = false;
  eHTTP::server::settings *settings;

  /// Forks a thread for handling the client.
  /// \param handler the function to call in the new thread for handling the client. One argument of the \p clientFd.
  void forkHandler(int clientFd, void (eHTTP::server::server:: *handler)(int));
  /// Reads a request from a client and serves the CGI or static file, then closes the connection.
  void handleClient(int clientFd);
  void handleClientTls(int clientFd);
  long long serveFile(int clientFd, httpParsing::AbsPath &path);
  long long serveFileTls(TLSServer &client, httpParsing::AbsPath &path);
  /// Executes \p cgiEndpoint and transmits the data between the client and the CGI endpoint.
  /// \param tcpIstream is the stream for reading from the TCP client.
  /// \param clientFd is the file descriptor for writing to the TCP client.
  /// \param path is the \p AbsPath requested by the client. It is provided to the CGI script for routing.
  /// \param cgiEndpoint the CGI endpoint information to execute.
  /// \param requestHeaders are the request headers sent by the client.
  /// \returns the number of bytes passed from the CGI script to the client.  (overflows are not caught.)
  long long serveCgi(std::istream &tcpIstream,
                     void *client,
                     httpParsing::AbsPath &path,
                     eHTTP::server::cgiEndpoint_t cgiEndpoint,
                     httpRequestHeaderCollection &requestHeaders,
                     bool tls);
  /// Tries to get a file name on the filesystem from \p path and \p settings.basePath.  It will search the default
  /// documents from the settings if \p is a folder.
  /// \param path is the requested path from the client.
  /// \param outFile is where the filesystem path will be stored if a file has been found.
  /// \returns true if a file has been found at the path. False if no file is found.
  bool getFileFromPath(httpParsing::AbsPath &path, std::string &outFile);
  /// Converts the header collection to a NULL-terminated array of strings for giving to the environment.
  /// \param headers the header collection to convert
  static char** headersToEnvArray(httpRequestHeaderCollection &headers);
  /// Frees the memory reserved for the environment array from \p headersToEnvArray
  static void freeEnvArray(char** env);

public:
  /// Constructs a HTTP server with no TLS.  Default document of index.html only.
  server(uint16_t port, std::string basePath);
  /// Constructs a HTTP(S) server with TLS.  Keeps a pointer to \p settings and \p TlsConfig.
  server(eHTTP::server::settings &settings);
  /// Destructs the server and cleans up any self-created variables.
  ~server();

  /// Adds an endpoint to the server settings.
  void addCgiEndpoint(std::string pathElement, std::string cgiPath, std::string cgiArguments);
  /// Adds a default document to the server settings.
  void addDefaultDocument(std::string document);
  /// Endless loop handling client requests.
  void serve();
  /// Sets the TLS configruation.  Keeps a pointer to the provided configuration.
  void setTlsConfiguration(TLSConfiguration *config) {
    this->settings->tlsConfiguration = config;
  }
};

}
}