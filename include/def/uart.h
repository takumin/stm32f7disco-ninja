#ifndef DEF_UART_H
#define DEF_UART_H

#ifdef __cplusplus
extern "C" {
#endif

// STM32F7HAL
#include <stm32f7xx.h>

// BaudRate
#define PHY_UART_BAUDRATE 115200

// Peripheral Base Address
#define PHY_UART_BASE USART1

// Peripheral Interrupt Number
#define PHY_UART_IRQn USART1_IRQn

// Peripheral Interrupt Function
#define Phy_Uart_IRQHandler USART1_IRQHandler

// Peripheral Reset
#define PHY_UART_FORCE_RESET() __HAL_RCC_USART1_FORCE_RESET()
#define PHY_UART_RELEASE_RESET() __HAL_RCC_USART1_RELEASE_RESET()

// Peripheral Clock Enable
#define PHY_UART_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()

// Peripheral Clock Disable
#define PHY_UART_CLK_DISABLE() __HAL_RCC_USART1_CLK_DISABLE()

// DMA Interrupt Number
#define PHY_UART_DMA_TX_IRQn DMA2_Stream7_IRQn
#define PHY_UART_DMA_RX_IRQn DMA2_Stream5_IRQn

// DMA Interrupt Function
#define Phy_Uart_DMA_Tx_IRQHandler DMA2_Stream7_IRQHandler
#define Phy_Uart_DMA_Rx_IRQHandler DMA2_Stream5_IRQHandler

// DMA Clock Enable
#define PHY_UART_DMA_CLK_ENABLE() __HAL_RCC_DMA2_CLK_ENABLE()

// DMA Clock Disable
#define PHY_UART_DMA_CLK_DISABLE() __HAL_RCC_DMA2_CLK_DISABLE()

// DMA Stream
#define PHY_UART_DMA_TX_STREAM DMA2_Stream7
#define PHY_UART_DMA_RX_STREAM DMA2_Stream5

// DMA Channel
#define PHY_UART_DMA_TX_CHANNEL DMA_CHANNEL_4
#define PHY_UART_DMA_RX_CHANNEL DMA_CHANNEL_4

// GPIO Clock Enable
#define PHY_UART_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define PHY_UART_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

// GPIO Clock Disable
#define PHY_UART_TX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define PHY_UART_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOB_CLK_DISABLE()

// GPIO Alternate Function
#define PHY_UART_TX_GPIO_AF GPIO_AF7_USART1
#define PHY_UART_RX_GPIO_AF GPIO_AF7_USART1

// GPIO Port
#define PHY_UART_TX_GPIO_PORT GPIOA
#define PHY_UART_RX_GPIO_PORT GPIOB

// GPIO Pin
#define PHY_UART_TX_GPIO_PIN GPIO_PIN_9
#define PHY_UART_RX_GPIO_PIN GPIO_PIN_7

#ifdef __cplusplus
}
#endif

#endif  // DEF_UART_H
