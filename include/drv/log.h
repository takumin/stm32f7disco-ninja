#ifndef DRV_LOG_H
#define DRV_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

// Event Type
typedef enum {
  // Reset
  Drv_Log_Event_Reset = 0x00000000,
  // String
  Drv_Log_Event_String,
  // Length
  Drv_Log_Event_Length,
  // Reserved
  Drv_Log_Event_Reserved = 0xffffffff
} Drv_Log_Event;

// Stream Type
typedef enum {
  // Uart
  Drv_Log_Stream_Uart = 0x00000000,
  // Reserved
  Drv_Log_Stream_Reserved = 0xffffffff
} Drv_Log_Stream;

// Queue Message
typedef struct {
  Drv_Log_Event  event;
  Drv_Log_Stream stream;
  uint8_t*       buf;
  uint16_t       len;
} Drv_Log_Message;

// CallBack Event
typedef void (*Drv_Log_Entry)(Drv_Log_Message*);

// Queue Handler
extern QueueHandle_t Drv_Log_QueueHandle;

// Task Handler
extern TaskHandle_t Drv_Log_TaskHandle;

// Initialize
extern void Drv_Log_Init(void);

// Execution
extern void Drv_Log_Task(void* args);

// Running Event
extern void Drv_Log_Trigger(Drv_Log_Message* msg);

#ifdef __cplusplus
}
#endif

#endif  // DRV_LOG_H
