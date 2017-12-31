#ifndef PHY_LED_H
#define PHY_LED_H

#ifdef __cplusplus
extern "C" {
#endif

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

// Task Notify
typedef enum {
  Phy_Led_Notify_HeartBeat = 1UL << 0,  // HeartBeat
} Phy_Led_Notify;

// Task Handler
extern TaskHandle_t Phy_Led_TaskHandle;

// Initialize
extern void Phy_Led_Init(void);

// Execution
extern void Phy_Led_Task(void* args);

#ifdef __cplusplus
}
#endif

#endif  // PHY_LED_H
