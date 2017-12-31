// STDC
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
// User
#include <def/macro.h>
#include <drv/log.h>
#include <phy/uart.h>

static void drv_log_callback_reset(Drv_Log_Message* msg);   // Reset Host Terminal
static void drv_log_callback_string(Drv_Log_Message* msg);  // Send String to Stream

// Event Table
ITCM static Drv_Log_Entry drv_log_event_table[Drv_Log_Event_Length] = {
    [Drv_Log_Event_Reset]  = drv_log_callback_reset,
    [Drv_Log_Event_String] = drv_log_callback_string,
};

// Running Event
ITCM void Drv_Log_Trigger(Drv_Log_Message* msg) {
  // Check Length
  if (msg->event > Drv_Log_Event_Length) {
    return;
  }

  // Callback Event
  drv_log_event_table[msg->event](msg);
}

// Reset Host Terminal
ITCM static void drv_log_callback_reset(Drv_Log_Message* msg) {
  const char buf[] = "\033c\033[3J";

  // Initialize Message
  msg->event  = Drv_Log_Event_String;
  msg->stream = Drv_Log_Stream_Uart;
  msg->len    = sizeof(buf);

  // Allocation Buffer
  configASSERT((msg->buf = pvPortMalloc(msg->len)) != NULL);

  // Copy Buffer
  memcpy(msg->buf, buf, msg->len);

  // Send Queue
  configASSERT(xQueueSendToFront(Drv_Log_QueueHandle, msg, 10) == pdPASS);
}

// Send String to Stream
ITCM static void drv_log_callback_string(Drv_Log_Message* msg) {
  // Uart Queue Message
  Phy_Uart_Message uart;

  // Switch Stream
  switch (msg->stream) {
    case Drv_Log_Stream_Uart:
      uart.buf = msg->buf;
      uart.len = msg->len;
      break;
    case Drv_Log_Stream_Reserved:
      break;
  }

  // Send Queue
  configASSERT(xQueueSend(Phy_Uart_Tx_QueueHandle, &uart, 10) == pdPASS);
}
