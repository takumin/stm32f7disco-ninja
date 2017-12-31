// STDC
#include <stddef.h>
#include <stdint.h>
// User
#include <def/macro.h>
#include <svc/crc.h>

// Table CRC-32-Castagnoli
DTCM static uint32_t crc_32_castagnoli_table[256];

// Make CRC-32-Castagnoli
ITCM void crc_32_castagnoli_make_table(void) {
  uint32_t c;
  for (size_t i = 0; i < 256; i++) {
    c = (uint32_t)i;
    for (size_t j = 0; j < 8; j++) {
      c = (c & 1) ? (0x82F63B78 ^ (c >> 1)) : (c >> 1);
    }
    crc_32_castagnoli_table[i] = c;
  }
}

// Calc CRC-32-Castagnoli
ITCM uint32_t crc_32_castagnoli(const uint8_t buf[], const size_t len) {
  uint32_t c = 0xffffffff;
  for (size_t i = 0; i < len; i++) {
    c = crc_32_castagnoli_table[(c ^ buf[i]) & 0xff] ^ (c >> 8);
  }
  return c ^ 0xffffffff;
}
