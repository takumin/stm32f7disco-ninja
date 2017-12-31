// STDC
#include <stdnoreturn.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <def/macro.h>
#include <def/uart.h>
#include <phy/uart.h>

// Context Switch Flag
static BaseType_t phy_uart_tx_context_switch;
static BaseType_t phy_uart_rx_context_switch;

// Interrupt Peripheral
ITCM void Phy_Uart_IRQHandler(void) {
  phy_uart_tx_context_switch = pdFALSE;
  phy_uart_rx_context_switch = pdFALSE;
  HAL_UART_IRQHandler(&Phy_Uart_HalHandle);
  portYIELD_FROM_ISR((phy_uart_tx_context_switch | phy_uart_rx_context_switch));
}

// Interrupt Tx DMA
ITCM void Phy_Uart_DMA_Tx_IRQHandler(void) {
  phy_uart_tx_context_switch = pdFALSE;
  HAL_DMA_IRQHandler(Phy_Uart_HalHandle.hdmatx);
  portYIELD_FROM_ISR(phy_uart_tx_context_switch);
}

// Interrupt Rx DMA
ITCM void Phy_Uart_DMA_Rx_IRQHandler(void) {
  phy_uart_rx_context_switch = pdFALSE;
  HAL_DMA_IRQHandler(Phy_Uart_HalHandle.hdmarx);
  portYIELD_FROM_ISR(phy_uart_rx_context_switch);
}

// Tx DMA Complete Callback
ITCM void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == PHY_UART_BASE) {
    vTaskNotifyGiveFromISR(Phy_Uart_Tx_TaskHandle, &phy_uart_tx_context_switch);
  }
}

// Rx DMA Complete Callback
ITCM void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == PHY_UART_BASE) {
    vTaskNotifyGiveFromISR(Phy_Uart_Rx_TaskHandle, &phy_uart_rx_context_switch);
  }
}

// Error Callback
noreturn void HAL_UART_ErrorCallback(UART_HandleTypeDef* UNUSED(huart)) {
  while (1) {
  }
}
