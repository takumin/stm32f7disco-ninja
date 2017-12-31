// STDC
#include <stdio.h>
#include <stdnoreturn.h>
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <app/hbt.h>
#include <def/macro.h>
#include <phy/led.h>
#include <phy/tim.h>
#include <svc/log.h>

// Execution
ITCM noreturn void App_Hbt_Task(void* UNUSED(args)) {
  TickType_t       prev   = xTaskGetTickCount();
  const TickType_t period = pdMS_TO_TICKS(500);
  // char             log[128];
  // memset(log, 0, sizeof(log));

  // Loop...
  while (1) {
    // Suspend
    vTaskDelayUntil(&prev, period);

    // Phy Led Task Notify
    xTaskNotify(Phy_Led_TaskHandle, Phy_Led_Notify_HeartBeat, eSetBits);

    // Debug Log
    // sprintf(log, "[%u.%u] HeartBeat", Phy_Tim_Get_1s_Timer(), Phy_Tim_Get_1s_Tick());
    // log_string(log);
  }
}
