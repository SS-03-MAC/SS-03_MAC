# Symmetric
Symmetric is an abstract class with helper methods for encrypting and decrypting
using a symmetric ciphers. Symmetric ciphers include both block and stream
ciphers, so care must be taken as to what mode is used.

## Guaranteed Methods

int encrypt(uint8_t \*output, uint8_t \*input, size_t count)

    Guaranteed method implemented by all symmetric ciphers. Encrypts count input
    bytes and places the result in output.


int decrypt(uint8_t \*output, uint8_t \*input, size_t count)

    Guaranteed method implemented by all symmetric ciphers. Encrypts count input
    bytes and places the result in output.


## AES
AES is a specific encryption algorithm implemented from FIPS specification.

static aes \*aes_128(uint8_t key[16]);

    Initializes a new AES cipher with a given 128-bit key.

static aes \*aes_192(uint8_t key[24]);

    Initializes a new AES cipher with a given 192-bit key.

static aes \*aes_256(uint8_t key[32]);

    Initializes a new AES cipher with a given 256-bit key.

aes(uint8_t \*key, size_t size);

    Initializes a new AES cipher with either an 128, 192, or 256 bit key and
    returns it.

uint32_t \*\_\_testing_copy_key();

    Testing method to dump expanded key.

## DES
DES is an older encryption algorithm standardized in FIPS 46-3.

uint64_t encrypt(uint64_t input);

    Encrypts a single block of input and returns the result.

uint64_t decrypt(uint64_t input);

    Decrypts a single block of input and returns the result.

des(uint8_t \*input, size_t count);

    Initializes DES from a key in byte array form.

des(uint64_t key);

    Initializes DES from a key in 64 bit unsigned integer form. 
