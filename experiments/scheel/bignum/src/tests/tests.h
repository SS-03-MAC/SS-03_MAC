#include "../lib/bigint.h"
#include "tests_addition.h"
#include "tests_equality.h"
#include "tests_multiplication.h"
#include <cassert>
#include <string>

std::string tests_n[] = {"Testing equality of zeros...",      "Testing equality of one...",
                         "Testing inequality of +/- one...",  "Testing equality ignores padding...",
                         "Testing comparison greater...",     "Testing comparison less...",
                         "Testing addition (small)...",       "Testing addition (overflows)...",
                         "Testing multiplication (small)...", "Testing multiplication (overflows)..."};

void *tests_f[] = {(void *)&test_equality_zeros,
                   (void *)&test_equality_one,
                   (void *)&test_inequality_one,
                   (void *)&test_equality_padding,
                   (void *)&test_compare_greater,
                   (void *)&test_compare_less,
                   (void *)&test_addition_small,
                   (void *)&test_addition_overflow,
                   (void *)&test_multiplication_small,
                   (void *)&test_multiplication_overflow,
                   NULL};
