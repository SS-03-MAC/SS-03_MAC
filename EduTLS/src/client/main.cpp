#include "../crypto/block/ecb.h"
#include "../crypto/entropy.h"
#include "../crypto/hash/hash.h"
#include "../crypto/hash/md.h"
#include "../crypto/hash/md5.h"
#include "../crypto/hash/sha1.h"
#include "../crypto/hash/sha2-224.h"
#include "../crypto/hash/sha2-256.h"
#include "../crypto/hash/sha2-384.h"
#include "../crypto/hash/sha2-512.h"
#include "../crypto/padding.h"
#include "../crypto/symmetric/3des.h"
#include "../crypto/symmetric/aes.h"
#include "../crypto/symmetric/des.h"
#include "../crypto/symmetric/rc4.h"
#include "../crypto/symmetric/symmetric.h"
#include "../crypto/utils.h"
#include "../encoding/base64.h"
#include "../encoding/der/der.h"
#include "../encoding/hex.h"
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
