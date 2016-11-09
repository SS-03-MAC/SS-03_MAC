#include "tests_base64.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing Base64 Encoding...", "Testing Base64 Decoding...",
};

void *tests_f[] = {(void *)&test_base64_encode, (void *)&test_base64_decode, NULL};
