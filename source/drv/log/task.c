// STDC
#include <stdnoreturn.h>
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
// User
#include <def/macro.h>
#include <drv/log.h>

// Execution
ITCM noreturn void Drv_Log_Task(void* UNUSED(args)) {
  // Queue Message
  Drv_Log_Message msg;

  // Initialize Message
  memset(&msg, 0, sizeof(Drv_Log_Message));

  // Clear Host Terminal
  Drv_Log_Trigger(&msg);

  // Loop...
  while (1) {
    // Wait Queue
    configASSERT(xQueueReceive(Drv_Log_QueueHandle, &msg, portMAX_DELAY) == pdPASS);

    // Running Event
    Drv_Log_Trigger(&msg);
  }
}
