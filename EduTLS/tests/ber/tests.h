#include "tests_bitstring.h"
#include "tests_boolean.h"
#include "tests_integer.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing BER Boolean Encoding...",        "Testing BER Boolean Decoding...",
    "Testing BER Unsigned Integers...",       "Testing BER Signed Integers...",
    "Testing BER Short Bistring Encoding...", "Testing BER Short Bistring Decoding...",
};

void *tests_f[] = {(void *)&test_ber_boolean_encode,
                   (void *)&test_ber_boolean_decode,
                   (void *)&test_ber_unsigned_integer,
                   (void *)&test_ber_signed_integer,
                   (void *)&test_ber_bitstring_short_encode,
                   (void *)&test_ber_bitstring_short_decode,
                   NULL};
