#include "../lib/bigint.h"
#include "tests_addition.h"
#include "tests_bitshift.h"
#include "tests_division.h"
#include "tests_equality.h"
#include "tests_exponentiation.h"
#include "tests_modulus.h"
#include "tests_multiplication.h"
#include <cassert>
#include <string>

std::string tests_n[] = {"Testing equality of zeros...",      "Testing equality of one...",
                         "Testing inequality of +/- one...",  "Testing equality ignores padding...",
                         "Testing comparison greater...",     "Testing comparison less...",
                         "Testing addition (small)...",       "Testing addition (overflows)...",
                         "Testing left shift (small)...",     "Testing right shift (small)...",
                         "Testing multiplication (small)...", "Testing multiplication (overflows)...",
                         "Testing division (small)...",       "Testing modulus (small)...",
                         "Testing exponentiation (small)...", "Testing modular exponentiation (small)..."};

void *tests_f[] = {(void *)&test_equality_zeros,
                   (void *)&test_equality_one,
                   (void *)&test_inequality_one,
                   (void *)&test_equality_padding,
                   (void *)&test_compare_greater,
                   (void *)&test_compare_less,
                   (void *)&test_addition_small,
                   (void *)&test_addition_overflow,
                   (void *)&test_left_shift_small,
                   (void *)&test_right_shift_small,
                   (void *)&test_multiplication_small,
                   (void *)&test_multiplication_overflow,
                   (void *)&test_division_small,
                   (void *)&test_modulus_small,
                   (void *)&test_exponentiation_small,
                   (void *)&test_modexp_small,
                   NULL};
