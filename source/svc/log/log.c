// STDC
#include <stdint.h>
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
// User
#include <drv/log.h>
#include <phy/tim.h>
#include <svc/log.h>

void log_string(const char* buf) {
  Drv_Log_Message msg = {.event = Drv_Log_Event_String, .buf = NULL, .len = 0};
  const char*     ptr = buf;

  while (*buf++) {
    msg.len++;
  }

  msg.len++;

  configASSERT((msg.buf = pvPortMalloc(msg.len)) != NULL);

  memcpy(msg.buf, ptr, msg.len);

  msg.buf[msg.len - 1] = '\n';

  configASSERT(xQueueSend(Drv_Log_QueueHandle, &msg, 10) == pdPASS);
}
