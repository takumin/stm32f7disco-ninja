#ifndef SVC_CRC_H
#define SVC_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

// STDC
#include <stddef.h>
#include <stdint.h>

extern void Svc_Crc_Init(void);

// CRC-16-IBM
extern void     crc_16_ibm_make_table(void);
extern uint16_t crc_16_ibm(const uint8_t buf[], const size_t len);

// CRC-32-Castagnoli
extern void     crc_32_castagnoli_make_table(void);
extern uint32_t crc_32_castagnoli(const uint8_t buf[], const size_t len);

#ifdef __cplusplus
}
#endif

#endif  // SVC_CRC_H
