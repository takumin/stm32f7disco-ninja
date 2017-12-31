// User
#include <svc/crc.h>

// Initialize
void Svc_Crc_Init(void) {
  // Make CRC Table
  crc_16_ibm_make_table();
  crc_32_castagnoli_make_table();
}
