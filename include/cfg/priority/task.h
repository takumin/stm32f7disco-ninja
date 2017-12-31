#ifndef CFG_PRIORITY_TASK_H
#define CFG_PRIORITY_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

// Phy Led
#define PHY_LED_TASK_PRIORITY (3)

// Phy Uart
#define PHY_UART_TX_TASK_PRIORITY (3)
#define PHY_UART_RX_TASK_PRIORITY (3)

// Drv Log
#define DRV_LOG_TASK_PRIORITY (2)

// App Hbt
#define APP_HBT_TASK_PRIORITY (1)

#ifdef __cplusplus
}
#endif

#endif  // CFG_PRIORITY_TASK_H
