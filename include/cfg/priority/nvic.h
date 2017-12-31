#ifndef CFG_PRIORITY_NVIC_H
#define CFG_PRIORITY_NVIC_H

#ifdef __cplusplus
extern "C" {
#endif

// Phy Uart
#define PHY_UART_NVIC_PRIORITY (10)
#define PHY_UART_DMA_TX_NVIC_PRIORITY (10)
#define PHY_UART_DMA_RX_NVIC_PRIORITY (10)

// Phy Tim
#define PHY_TIM_1S_NVIC_PRIORITY (0)
#define PHY_TIM_1MS_NVIC_PRIORITY (0)

#ifdef __cplusplus
}
#endif

#endif  // CFG_PRIORITY_NVIC_H
