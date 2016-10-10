#include "tests_rc4.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing RC4 key stream one...", "Testing RC4 key stream two...",
};

void *tests_f[] = {(void *)&test_rc4_stream_one, (void *)&test_rc4_stream_two, NULL};
