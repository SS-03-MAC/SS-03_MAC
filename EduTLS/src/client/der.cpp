#include "../encoding/der/der.h"
#include "../encoding/base64.h"
#include "../encoding/constants/asn1.h"
#include "../encoding/hex.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "der.h"

void prc(char c, int count) {
  for (int i = 0; i < count; i++) {
    printf("%c", c);
  }
}

void parse_der(uint8_t *data, size_t data_length, int depth) {
  if (data_length == 0) {
    return;
  }

  size_t d_p = 0;

  while (d_p < data_length) {
    uint8_t type = data[d_p + 0];
    size_t contents_length = decode_length(&(data[d_p + 1]));
    size_t header_length = 1 + decode_length_length(&(data[d_p + 1]));

    if (d_p + contents_length + header_length > data_length) {
      prc('\t', depth);
      printf("Error! Extends past contents length: %zu %zu %zu %zu %02x %02x %02x %02x\n", data_length, d_p,
             contents_length, header_length, type, data[d_p + 1], data[d_p + 2], data[d_p + 3]);
      return;
    }

    if (data_length - contents_length - d_p < 2) {
      prc('\t', depth);
      printf("Error! Malformed contents length.\n");
      return;
    }

    if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_CONSTRUCTED | ASN_SEQUENCE_CLASS)) {
      prc('\t', depth);
      printf("SEQUENCE - len(%zu)\n", data_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_CONSTRUCTED | ASN_SET_CLASS)) {
      prc('\t', depth);
      printf("SET - len(%zu)\n", data_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if (type == (BER_IDENTIFIER_CLASS_CONTEXT | BER_IDENTIFIER_TYPE_CONSTRUCTED)) {
      prc('\t', depth);
      printf("CONTEXT CONSTRUCTED TAG [%02x] - len(%zu)\n", type & 0x1F, data_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_PRINTABLE_STRING_CLASS)) {
      prc('\t', depth);
      printf("PRINTABLE STRING - len(%zu)\n", data_length);
      prc('\t', depth + 1);
      size_t ps_length = decode_printablestring_length(&(data[d_p]));
      uint8_t ps[ps_length + 1];
      decode_printablestring((char *)ps, &(data[d_p]), ps_length + header_length);
      ps[ps_length] = '\0';
      printf("%s\n", (char *)ps);
    } else {
      prc('\t', depth);
      printf("Unknown Tag %02x %02x %02x %zu %zu\n", type, data[d_p + 1], data[d_p + 2], header_length,
             contents_length);
    }

    d_p += header_length + contents_length;
  }
}

void handle_parsing(const char *filename) {
  size_t length;

  FILE *fp = fopen(filename, "r");
  fseek(fp, 0L, SEEK_END);
  length = ftell(fp);
  rewind(fp);

  uint8_t data[length];

  for (size_t i = 0; i < length; i++) {
    data[i] = fgetc(fp);
  }

  fclose(fp);

  parse_der(data, length, 0);
}
