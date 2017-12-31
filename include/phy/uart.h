#ifndef PHY_UART_H
#define PHY_UART_H

#ifdef __cplusplus
extern "C" {
#endif

// STDC
#include <stdint.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

// Queue Message
typedef struct {
  uint8_t* buf;
  uint16_t len;
} Phy_Uart_Message;

// Hal Handler
extern UART_HandleTypeDef Phy_Uart_HalHandle;

// Queue Handler
extern QueueHandle_t Phy_Uart_Tx_QueueHandle;
extern QueueHandle_t Phy_Uart_Rx_QueueHandle;

// Task Handler
extern TaskHandle_t Phy_Uart_Tx_TaskHandle;
extern TaskHandle_t Phy_Uart_Rx_TaskHandle;

// Initialize
extern void Phy_Uart_Init(void);

// Execution Tx
extern void Phy_Uart_Tx_Task(void* args);

// Execution Rx
extern void Phy_Uart_Rx_Task(void* args);

// Interrupt Peripheral
extern void Phy_Uart_IRQHandler(void);

// Interrupt Tx DMA
extern void Phy_Uart_DMA_Tx_IRQHandler(void);

// Interrupt Rx DMA
extern void Phy_Uart_DMA_Rx_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif  // PHY_UART_H
