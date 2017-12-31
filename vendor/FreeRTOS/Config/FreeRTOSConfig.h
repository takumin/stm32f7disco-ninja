#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* STM32F7HAL */
#include <stm32f7xx.h>
/* User Config */
#include <cfg/cfg.h>

/* General */
#define configCPU_CLOCK_HZ (SystemCoreClock)
#define configTICK_RATE_HZ ((TickType_t)1000)
#define configMINIMAL_STACK_SIZE (CFG_MINIMAL_STACK_SIZE)
#define configTOTAL_HEAP_SIZE (CFG_TOTAL_HEAP_SIZE)
#define configAPPLICATION_ALLOCATED_HEAP (1)
#define configSUPPORT_STATIC_ALLOCATION (1)
#define configSUPPORT_DYNAMIC_ALLOCATION (1)
#define configMAX_TASK_NAME_LEN (32)
#define configQUEUE_REGISTRY_SIZE (32)
#define configUSE_PREEMPTION (1)
#define configUSE_16_BIT_TICKS (0)
#define configUSE_IDLE_HOOK (1)
#define configUSE_TICK_HOOK (0)
#define configUSE_TIMERS (0)

/* Idle Counter */
#if configUSE_IDLE_HOOK == 1
extern volatile uint32_t xIdleCount;
#endif

/* Software Timers */
#if configUSE_TIMERS == 1
#define configTIMER_TASK_PRIORITY (7)
#define configTIMER_QUEUE_LENGTH (5)
#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE)
#endif

/* Interrupt Priority */
#define configMAX_PRIORITIES (CFG_MAX_PRIORITY)
#define configPRIO_BITS __NVIC_PRIO_BITS
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY (0xf)
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY (5)
#define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* Enable Function */
#define INCLUDE_vTaskDelay (1)
#define INCLUDE_vTaskDelayUntil (1)
#define INCLUDE_xTaskGetCurrentTaskHandle (1)

/* Replace assert.h */
#define configASSERT(x)         \
  do {                          \
    if ((x) == 0) {             \
      taskDISABLE_INTERRUPTS(); \
      while (1);                \
    }                           \
  } while (0);

/* Require FreeRTOS */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

/* Use FreeRTOS 10 */
#define configENABLE_BACKWARD_COMPATIBILITY (0)

#ifdef __cplusplus
}
#endif

#endif /* FREERTOS_CONFIG_H */
