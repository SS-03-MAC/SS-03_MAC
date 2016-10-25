#include "tests_hmac.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing HMAC MD5 with first test vector...", "Testing HMAC MD5 with second test vector...",
    "Testing HMAC MD5 with third test vector...",
};

void *tests_f[] = {(void *)&test_hmac_md5_vector_one, (void *)&test_hmac_md5_vector_two,
                   (void *)&test_hmac_md5_vector_three, NULL};
