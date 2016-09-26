#include "tests_sha2-224.h"
#include "tests_sha2-256.h"
#include "tests_sha2-384.h"
#include "tests_sha2-512.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing SHA2-224 with null string...",    "Testing SHA2-224 with foxdog...",
    "Testing SHA2-224 with foxdog(period)...", "Testing SHA2-256 with null string...",
    "Testing SHA2-256 with foxdog...",         "Testing SHA2-256 with foxdog(period)...",
    "Testing SHA2-384 with null string...",    "Testing SHA2-384 with foxdog...",
    "Testing SHA2-384 with foxdog(period)...", "Testing SHA2-512 with null string...",
    "Testing SHA2-512 with foxdog...",         "Testing SHA2-512 with foxdog(period)...",
};

void *tests_f[] = {(void *)&test_sha2_224_null,
                   (void *)&test_sha2_224_foxdog,
                   (void *)&test_sha2_224_foxdog_period,
                   (void *)&test_sha2_256_null,
                   (void *)&test_sha2_256_foxdog,
                   (void *)&test_sha2_256_foxdog_period,
                   (void *)&test_sha2_384_null,
                   (void *)&test_sha2_384_foxdog,
                   (void *)&test_sha2_384_foxdog_period,
                   (void *)&test_sha2_512_null,
                   (void *)&test_sha2_512_foxdog,
                   (void *)&test_sha2_512_foxdog_period,
                   NULL};
