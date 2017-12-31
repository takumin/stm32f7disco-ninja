// STDC
#include <string.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <cfg/cfg.h>
#include <def/led.h>
#include <phy/led.h>

// Task Handler
TaskHandle_t Phy_Led_TaskHandle;

// Task Stack
static StackType_t phy_led_task_stack[PHY_LED_STACK_SIZE];

// Task Buffer
static StaticTask_t phy_led_task_control;

// Initialize
void Phy_Led_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;

  // Clear Global Variables
  Phy_Led_TaskHandle = NULL;

  // Clear Static Variables
  memset(&phy_led_task_stack, 0x55, sizeof(phy_led_task_stack));
  memset(&phy_led_task_control, 0, sizeof(phy_led_task_control));

  // Clear Local Variables
  memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));

  // GPIO Ports Clock Enable
  PHY_LED1_GPIO_CLK_ENABLE();

  // Configure GPIO Struct : Common
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = 0;

  // Configure GPIO Struct : LED1
  GPIO_InitStruct.Pin = PHY_LED1_GPIO_PIN;
  HAL_GPIO_Init(PHY_LED1_GPIO_PORT, &GPIO_InitStruct);

  // Reset GPIO State
  HAL_GPIO_WritePin(PHY_LED1_GPIO_PORT, PHY_LED1_GPIO_PIN, GPIO_PIN_RESET);

  // Create Task
  configASSERT((Phy_Led_TaskHandle = xTaskCreateStatic(
                    // Function Pointer
                    Phy_Led_Task,
                    // Task Name
                    "Phy/Led/Task",
                    // Stack Size
                    PHY_LED_STACK_SIZE,
                    // Task Parameter
                    NULL,
                    // Task Priority
                    PHY_LED_TASK_PRIORITY,
                    // Stack Area
                    phy_led_task_stack,
                    // Control Block
                    &phy_led_task_control)) != NULL);
}
