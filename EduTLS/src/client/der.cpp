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
      printf("SEQUENCE - len(%zu)\n", contents_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_CONSTRUCTED | ASN_SET_CLASS)) {
      prc('\t', depth);
      printf("SET - len(%zu)\n", contents_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if ((type & (BER_IDENTIFIER_CLASS_MASK | BER_IDENTIFIER_TYPE_MASK)) ==
               (BER_IDENTIFIER_CLASS_CONTEXT | BER_IDENTIFIER_TYPE_CONSTRUCTED)) {
      prc('\t', depth);
      printf("CONTEXT CONSTRUCTED CLASS [%02x] - len(%zu)\n", type & 0x1F, contents_length);
      parse_der(&(data[d_p + header_length]), contents_length, depth + 1);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_PRINTABLE_STRING_CLASS)) {
      prc('\t', depth);
      size_t ps_length = decode_printablestring_length(&(data[d_p]));
      printf("PRINTABLE STRING - len(%zu)\n", ps_length);
      prc('\t', depth + 1);
      uint8_t ps[ps_length + 1];
      decode_printablestring((char *)ps, &(data[d_p]), ps_length + header_length);
      ps[ps_length] = '\0';
      printf("%s\n", (char *)ps);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OCTET_STRING_CLASS)) {
      prc('\t', depth);
      size_t os_length = decode_octetstring_length(&(data[d_p]));
      printf("OCTET STRING - len(%zu)\n", os_length);
      prc('\t', depth + 1);
      uint8_t os[os_length];
      decode_octetstring(os, &(data[d_p]), os_length + header_length);
      char hex[2 * os_length + 1];
      toHex(hex, os, os_length);
      hex[2 * os_length] = '\0';
      printf("%s\n", hex);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BIT_STRING_CLASS)) {
      prc('\t', depth);
      size_t bt_length = decode_bitstring_length(&(data[d_p]));
      printf("BIT STRING - len(%zu)\n", bt_length);
      prc('\t', depth + 1);
      uint8_t bt[bt_length];
      uint8_t unused = decode_bitstring(bt, &(data[d_p]), contents_length + header_length);
      char hex[2 * bt_length + 1];
      toHex(hex, bt, bt_length);
      hex[2 * bt_length] = '\0';
      printf("%s\n", hex);
      prc('\t', depth + 1);
      printf("Unused: %02d\n", unused);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_BOOLEAN_CLASS)) {
      prc('\t', depth);
      bool b_result = false;
      printf("BOOLEAN - len(%zu)\n", contents_length);
      prc('\t', depth + 1);
      decode_boolean(&b_result, &(data[d_p]));
      printf("%s\n", b_result ? "true" : "false");
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_NULL_CLASS)) {
      prc('\t', depth);
      printf("NULL CLASS\n");
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_UTC_TIME_CLASS)) {
      prc('\t', depth);
      printf("UTC Time - len(%zu)\n", contents_length);
      UTCTime t;
      decode_utctime(&t, &(data[d_p]));
      prc('\t', depth + 1);
      printf("%02d/%02d/%02d %02d:%02d:%02d Z\n", t.year, t.month, t.day, t.hour, t.minute, t.second);
    } else if (type == (BER_IDENTIFIER_CLASS_UNIVERSAL | BER_IDENTIFIER_TYPE_PRIMITIVE | ASN_OBJECT_IDENTIFIER_CLASS)) {
      prc('\t', depth);
      size_t o_length = decode_objectidentifier_length(&(data[d_p]), contents_length + header_length);
      printf("Object Identifier - len(%zu)\n", o_length);
      uint32_t o[o_length];
      decode_objectidentifier(o, &(data[d_p]), contents_length + header_length);
      prc('\t', depth + 1);
      printf("{");
      for (size_t i = 0; i < o_length; i++) {
        printf(" %d", o[i]);
      }
      printf(" }\n");
    } else {
      prc('\t', depth);
      printf("Unknown Tag t: %02x h: %zu c: %zu\n", type, header_length, contents_length);
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
