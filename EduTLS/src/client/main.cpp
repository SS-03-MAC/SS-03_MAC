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

#include <cstdio>
#include <cstring>

int main(int argc, const char *argv[]) {
  if (argc == 3 && strncmp(argv[1], "der", 3) == 0) {
    handle_parsing(argv[2]);
  } else if (argc == 2 && strncmp(argv[1], "test", 4) == 0) {
    uint8_t buffer[10];
    uint8_t padded[15];
    edutls_rand_bytes(buffer, 10);

    printf("Entropy: ");
    char buf_out[21];
    buf_out[20] = '\0';
    toHex(buf_out, buffer, 10);
    printf("%s\n", buf_out);

    edutls_pad_pkcs1(padded, 15, buffer, 10, PKCS1_BT1);
    printf("PKCS1.1: ");
    for (int i = 0; i < 15; i++) {
      printf("%02x", padded[i]);
    }
    printf("\n");

    bool result = edutls_unpad_pkcs1(buffer, padded, 15);
    printf("UNPKCS1: ");
    for (int i = 0; i < 10; i++) {
      printf("%02x", buffer[i]);
    }
    printf("\n");
    printf("Valid? %d\n\n", result);

    edutls_pad_pkcs1(padded, 15, buffer, 10, PKCS1_BT2);
    printf("PKCS1.2: ");
    for (int i = 0; i < 15; i++) {
      printf("%02x", padded[i]);
    }
    printf("\n");

    result = edutls_unpad_pkcs1(buffer, padded, 15);
    printf("UNPKCS1: ");
    for (int i = 0; i < 10; i++) {
      printf("%02x", buffer[i]);
    }
    printf("\n");
    printf("Valid? %d\n\n", result);

    edutls_pad_pkcs7(padded, buffer, 10, 15);
    printf("PKCS7:   ");
    for (int i = 0; i < 15; i++) {
      printf("%02x", padded[i]);
    }
    printf("\n\n");

    result = edutls_unpad_pkcs7(buffer, padded, 15, 15);
    printf("UNPKCS7: ");
    for (int i = 0; i < 10; i++) {
      printf("%02x", buffer[i]);
    }
    printf("\n");
    printf("Valid? %d\n\n", result);
  } else {
    printf("%s - the EduTLS client program\n", argv[0]);
    printf("Usage:\n\tder <file> - Parse the DER encoded <file>.\n\ttest - Run a quick self check.\n\n");
  }

  return 0;
}
