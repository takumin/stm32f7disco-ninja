#ifndef CFG_REGION_STACK_H
#define CFG_REGION_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

// Minimal Stack Size
#define CFG_MINIMAL_STACK_SIZE (128)

// Phy Led
#define PHY_LED_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)

// Phy Uart
#define PHY_UART_TX_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)
#define PHY_UART_RX_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)

// Drv Log
#define DRV_LOG_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)

// App Hbt
#define APP_HBT_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)

#ifdef __cplusplus
}
#endif

#endif  // CFG_REGION_STACK_H
