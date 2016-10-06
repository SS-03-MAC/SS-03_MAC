#include "tests_aes128.h"
#include "tests_aes192.h"
#include "tests_aes256.h"

#include <cassert>
#include <string>

std::string tests_n[] = {
    "Testing AES-128 Key Expansion...", "Testing AES-128 Encryption...",  "Testing AES-128 Decryption...",
    "Testing AES-128 AVS GFSbox...",    "Testing AES-128 AVS KeySbox...", "Testing AES-192 Key Expansion...",
    "Testing AES-192 Encryption...",    "Testing AES-192 Decryption...",  "Testing AES-192 AVS GFSbox...",
    "Testing AES-256 Key Expansion...", "Testing AES-256 Encryption...",  "Testing AES-256 Decryption...",
    "Testing AES-256 AVS GFSbox...",
};

void *tests_f[] = {(void *)&test_aes128_key_expansion, (void *)&test_aes128_encrypt,
                   (void *)&test_aes128_decrypt,       (void *)&test_aes128_avs_gfsbox,
                   (void *)&test_aes128_avs_keysbox,   (void *)&test_aes192_key_expansion,
                   (void *)&test_aes192_encrypt,       (void *)&test_aes192_decrypt,
                   (void *)&test_aes192_avs_gfsbox,    (void *)&test_aes256_key_expansion,
                   (void *)&test_aes256_encrypt,       (void *)&test_aes256_decrypt,
                   (void *)&test_aes256_avs_gfsbox,    NULL};
