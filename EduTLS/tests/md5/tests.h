#include "tests_md5.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing MD5 with null string...", "Testing MD5 with foxdog...", "Testing MD5 with foxdog(period)...",
};

void *tests_f[] = {(void *)&test_md5_null, (void *)&test_md5_foxdog, (void *)&test_md5_foxdog_period, NULL};
