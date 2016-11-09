#include "../../src/encoding/base64.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>

int test_base64_encode() {
  char encoded[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t str[6] = {'f', 'o', 'o', 'b', 'a', 'r'};
  toBase64(encoded, str, 0);
  assert(encoded[0] == 0x00);

  toBase64(encoded, str, 1);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'g');
  assert(encoded[2] == '=');
  assert(encoded[3] == '=');

  toBase64(encoded, str, 2);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'm');
  assert(encoded[2] == '8');
  assert(encoded[3] == '=');

  toBase64(encoded, str, 3);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'm');
  assert(encoded[2] == '9');
  assert(encoded[3] == 'v');

  toBase64(encoded, str, 4);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'm');
  assert(encoded[2] == '9');
  assert(encoded[3] == 'v');
  assert(encoded[4] == 'Y');
  assert(encoded[5] == 'g');
  assert(encoded[6] == '=');
  assert(encoded[7] == '=');

  toBase64(encoded, str, 5);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'm');
  assert(encoded[2] == '9');
  assert(encoded[3] == 'v');
  assert(encoded[4] == 'Y');
  assert(encoded[5] == 'm');
  assert(encoded[6] == 'E');
  assert(encoded[7] == '=');

  toBase64(encoded, str, 6);
  assert(encoded[0] == 'Z');
  assert(encoded[1] == 'm');
  assert(encoded[2] == '9');
  assert(encoded[3] == 'v');
  assert(encoded[4] == 'Y');
  assert(encoded[5] == 'm');
  assert(encoded[6] == 'F');
  assert(encoded[7] == 'y');

  return 0;
}

int test_base64_decode() {
  uint8_t str[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  /*
   BASE64("f") = "Zg=="
   BASE64("fo") = "Zm8="
   BASE64("foo") = "Zm9v"
   BASE64("foob") = "Zm9vYg=="
   BASE64("fooba") = "Zm9vYmE="
   BASE64("foobar") = "Zm9vYmFy"
  */
  char encoded[6][9] = {
      "Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy",
  };

  fromBase64(str, encoded[0], 4);
  assert(str[0] == 'f');

  fromBase64(str, encoded[1], 4);
  assert(str[0] == 'f');
  assert(str[1] == 'o');

  fromBase64(str, encoded[2], 4);
  assert(str[0] == 'f');
  assert(str[1] == 'o');
  assert(str[2] == 'o');

  fromBase64(str, encoded[3], 8);
  assert(str[0] == 'f');
  assert(str[1] == 'o');
  assert(str[2] == 'o');
  assert(str[3] == 'b');

  fromBase64(str, encoded[4], 8);
  assert(str[0] == 'f');
  assert(str[1] == 'o');
  assert(str[2] == 'o');
  assert(str[3] == 'b');
  assert(str[4] == 'a');

  fromBase64(str, encoded[5], 8);
  assert(str[0] == 'f');
  assert(str[1] == 'o');
  assert(str[2] == 'o');
  assert(str[3] == 'b');
  assert(str[4] == 'a');
  assert(str[5] == 'r');

  return 0;
}
