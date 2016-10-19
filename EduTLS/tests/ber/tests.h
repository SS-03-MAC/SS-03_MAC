#include "tests_boolean.h"
#include "tests_ia5string.h"
#include "tests_integer.h"
#include "tests_objectidentifier.h"
#include "tests_octetstring.h"
#include "tests_printablestring.h"
#include "tests_utctime.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing BER Boolean Encoding...",
    "Testing BER Boolean Decoding...",
    "Testing BER Unsigned Integers...",
    "Testing BER Signed Integers...",
    "Testing BER Short Octet String Encoding...",
    "Testing BER Short Octet String Decoding...",
    "Testing BER Long Octet String Encoding...",
    "Testing BER Long Octet String Decoding...",
    "Testing BER Short IA5 String Encoding...",
    "Testing BER Short IA5 String Decoding...",
    "Testing BER Short Printable String Encoding...",
    "Testing BER Short Printable String Decoding...",
    "Testing BER Object Identifier Encoding...",
    "Testing BER Object Identifier Decoding...",
    "Testing BER UTCTime Encoding...",
    "Testing BER UTCTime Decoding...",
};

void *tests_f[] = {(void *)&test_ber_boolean_encode,
                   (void *)&test_ber_boolean_decode,
                   (void *)&test_ber_unsigned_integer,
                   (void *)&test_ber_signed_integer,
                   (void *)&test_ber_octetstring_short_encode,
                   (void *)&test_ber_octetstring_short_decode,
                   (void *)&test_ber_octetstring_long_encode,
                   (void *)&test_ber_octetstring_long_decode,
                   (void *)&test_ber_ia5string_short_encode,
                   (void *)&test_ber_ia5string_short_decode,
                   (void *)&test_ber_printablestring_short_encode,
                   (void *)&test_ber_printablestring_short_decode,
                   (void *)&test_ber_objectidentifier_encode,
                   (void *)&test_ber_objectidentifier_decode,
                   (void *)&test_ber_utctime_encode,
                   (void *)&test_ber_utctime_decode,
                   NULL};
