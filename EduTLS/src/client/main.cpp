#include "../crypto/crypto.h"
#include "../tls/tls.h"
#include "der.h"
#include "server.h"

#include <cstdio>
#include <cstring>

int main(int argc, const char *argv[]) {
  if (argc == 3 && strncmp(argv[1], "der", 3) == 0) {
    handle_parsing(argv[2]);
  } else if (argc == 2 && strncmp(argv[1], "server", 6) == 0) {
    serve();
  } else {
    printf("%s - the EduTLS client program\n", argv[0]);
    printf("Usage:\n\tder <file> - Parse the DER encoded <file>.\n\tserver - Run a debug TLS server.\n\n");
  }

  return 0;
}
