// STDC
#include <stdnoreturn.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
// User
#include <def/macro.h>
#include <phy/uart.h>

// Execution Tx
ITCM noreturn void Phy_Uart_Tx_Task(void* UNUSED(args)) {
  // Queue Message
  Phy_Uart_Message msg;

  // Loop...
  while (1) {
    // Wait Queue
    configASSERT(xQueueReceive(Phy_Uart_Tx_QueueHandle, &msg, portMAX_DELAY) == pdPASS);

    // Check Buffer
    configASSERT(msg.buf != NULL);

    // Check Length
    configASSERT(msg.len > 0);

    // Send Hal DMA
    configASSERT(HAL_UART_Transmit_DMA(&Phy_Uart_HalHandle, msg.buf, msg.len) == HAL_OK);

    // Wait Task Notify
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(10));

    // Free Memory
    vPortFree(msg.buf);
  }
}

// Execution Rx
ITCM noreturn void Phy_Uart_Rx_Task(void* UNUSED(args)) {
  // Loop...
  while (1) {
    // Wait Task Notify
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  }
}
