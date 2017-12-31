#ifndef APP_HBT_H
#define APP_HBT_H

#ifdef __cplusplus
extern "C" {
#endif

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

// Task Handler
extern TaskHandle_t App_Hbt_TaskHandle;

// Initialize
extern void App_Hbt_Init(void);

// Execution
extern void App_Hbt_Task(void* args);

#ifdef __cplusplus
}
#endif

#endif  // APP_HBT_H
