#include "tests_des.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing DES Encryption...", "Testing DES Decryption...",
};

void *tests_f[] = {(void *)&test_des_encrypt, (void *)&test_des_decrypt, NULL};
