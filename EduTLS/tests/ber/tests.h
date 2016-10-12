#include "tests_boolean.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing BER Boolean Encoding...", "Testing BER Boolean Decoding...",
};

void *tests_f[] = {(void *)&test_ber_boolean_encode, (void *)&test_ber_boolean_decode, NULL};
