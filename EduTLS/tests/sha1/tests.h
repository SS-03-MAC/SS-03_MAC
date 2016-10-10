#include "tests_sha1.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing SHA1 with null string...", "Testing SHA1 with foxdog...", "Testing SHA1 with foxdog(period)...",
};

void *tests_f[] = {(void *)&test_sha1_null, (void *)&test_sha1_foxdog, (void *)&test_sha1_foxdog_period, NULL};
