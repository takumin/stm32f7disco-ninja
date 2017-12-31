// User
#include <app/hbt.h>
#include <drv/log.h>
#include <phy/led.h>
#include <phy/tim.h>
#include <phy/uart.h>
#include <svc/crc.h>
#include <svc/init.h>

void Svc_Init_Startup(void) {
  // Initialize Svc Crc
  Svc_Crc_Init();

  // Initialize Phy Tim
  Phy_Tim_Init();

  // Initialize Phy Led
  Phy_Led_Init();

  // Initialize Phy Uart
  Phy_Uart_Init();

  // Initialize Drv Log
  Drv_Log_Init();

  // Initialize App Hbt
  App_Hbt_Init();
}
