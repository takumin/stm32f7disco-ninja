// STDC
#include <stdint.h>
#include <stdnoreturn.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <def/led.h>
#include <def/macro.h>
#include <phy/led.h>

// Execution
ITCM noreturn void Phy_Led_Task(void* UNUSED(args)) {
  // Notify Value
  uint32_t notify;

  // Loop...
  while (1) {
    // Wait Task Notify
    xTaskNotifyWait(0, UINT32_MAX, &notify, portMAX_DELAY);

    // Check HeartBeat
    if ((notify & Phy_Led_Notify_HeartBeat)) {
      // Toogle LED
      HAL_GPIO_TogglePin(PHY_LED1_GPIO_PORT, PHY_LED1_GPIO_PIN);
    }
  }
}
