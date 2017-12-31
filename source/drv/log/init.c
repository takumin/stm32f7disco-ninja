// STDC
#include <string.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <cfg/cfg.h>
#include <drv/log.h>

// Queue Handler
QueueHandle_t Drv_Log_QueueHandle;

// Task Handler
TaskHandle_t Drv_Log_TaskHandle;

// Queue Stack
static uint8_t drv_log_queue_stack[sizeof(Drv_Log_Message) * DRV_LOG_QUEUE_SIZE];

// Queue Control
static StaticQueue_t drv_log_queue_control;

// Task Stack
static StackType_t drv_log_task_stack[DRV_LOG_STACK_SIZE];

// Task Buffer
static StaticTask_t drv_log_task_control;

// Initialize
void Drv_Log_Init(void) {
  // Clear Global Variables
  Drv_Log_QueueHandle = NULL;
  Drv_Log_TaskHandle  = NULL;

  // Clear Static Variables
  memset(&drv_log_queue_stack, 0x55, sizeof(drv_log_queue_stack));
  memset(&drv_log_queue_control, 0, sizeof(drv_log_queue_control));
  memset(&drv_log_task_stack, 0x55, sizeof(drv_log_task_stack));
  memset(&drv_log_task_control, 0, sizeof(drv_log_task_control));

  // Create Queue
  configASSERT((Drv_Log_QueueHandle = xQueueCreateStatic(
                    // Queue Size
                    DRV_LOG_QUEUE_SIZE,
                    // Item Size
                    sizeof(Drv_Log_Message),
                    // Stack Area
                    drv_log_queue_stack,
                    // Control Block
                    &drv_log_queue_control)) != NULL);

  // Configure Queue Name
  vQueueAddToRegistry(Drv_Log_QueueHandle, "Drv/Log/Queue");

  // Create Task
  configASSERT((Drv_Log_TaskHandle = xTaskCreateStatic(
                    // Function Pointer
                    Drv_Log_Task,
                    // Task Name
                    "Drv/Log/Task",
                    // Stack Size
                    DRV_LOG_STACK_SIZE,
                    // Task Parameter
                    NULL,
                    // Task Priority
                    DRV_LOG_TASK_PRIORITY,
                    // Stack Area
                    drv_log_task_stack,
                    // Control Block
                    &drv_log_task_control)) != NULL);
}
