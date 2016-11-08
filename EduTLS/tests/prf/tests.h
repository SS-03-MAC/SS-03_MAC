#include "tests_prf.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing PRF SHA256...",
};

void *tests_f[] = {(void *)&test_prf_sha256, NULL};
