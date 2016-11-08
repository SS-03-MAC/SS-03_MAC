#include "tests_rsa.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing RSA decryption...",
};

void *tests_f[] = {(void *)&test_rsa_decrypt, NULL};
