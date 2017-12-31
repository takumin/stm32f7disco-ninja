#ifndef CFG_CFG_H
#define CFG_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

// Total Heap Size
#define CFG_TOTAL_HEAP_SIZE (1024 * 32)

// FreeRTOS
#define CFG_MAX_PRIORITY (8)

// Stack
#include <cfg/region/stack.h>

// Queue
#include <cfg/region/queue.h>

// NVIC
#include <cfg/priority/nvic.h>

// Task
#include <cfg/priority/task.h>

#ifdef __cplusplus
}
#endif

#endif  // CFG_CFG_H
