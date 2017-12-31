// STDC
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <app/hbt.h>
#include <cfg/cfg.h>

// Task Handler
TaskHandle_t App_Hbt_TaskHandle;

// Task Stack
static StackType_t app_hbt_task_stack[APP_HBT_STACK_SIZE];

// Task Buffer
static StaticTask_t app_hbt_task_control;

// Initialize
void App_Hbt_Init(void) {
  // Clear Global Variables
  App_Hbt_TaskHandle = NULL;

  // Clear Static Variables
  memset(&app_hbt_task_stack, 0x55, sizeof(app_hbt_task_stack));
  memset(&app_hbt_task_control, 0, sizeof(app_hbt_task_control));

  // Create Task
  configASSERT((App_Hbt_TaskHandle = xTaskCreateStatic(
                    // Function Pointer
                    App_Hbt_Task,
                    // Task Name
                    "App/Hbt/Task",
                    // Stack Size
                    APP_HBT_STACK_SIZE,
                    // Task Parameter
                    NULL,
                    // Task Priority
                    APP_HBT_TASK_PRIORITY,
                    // Stack Area
                    app_hbt_task_stack,
                    // Control Block
                    &app_hbt_task_control)) != NULL);
}
