// STDC
#include <stddef.h>
#include <stdint.h>
// User
#include <def/macro.h>
#include <svc/crc.h>

// Table CRC-16-IBM
DTCM static uint16_t crc_16_ibm_table[256];

// Make CRC-16-IBM
ITCM void crc_16_ibm_make_table(void) {
  uint16_t c;
  for (size_t i = 0; i < 256; i++) {
    c = (uint16_t)i;
    for (size_t j = 0; j < 8; j++) {
      c = (c & 1) ? (0xA001 ^ (c >> 1)) : (c >> 1);
    }
    crc_16_ibm_table[i] = c;
  }
}

// Calc CRC-16-IBM
ITCM uint16_t crc_16_ibm(const uint8_t buf[], const size_t len) {
  uint16_t c = 0xffff;
  for (size_t i = 0; i < len; i++) {
    c = crc_16_ibm_table[(c ^ buf[i]) & 0xff] ^ (c >> 8);
  }
  return c;
}
