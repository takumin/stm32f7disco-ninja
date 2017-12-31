// STDC
#include <stdint.h>
#include <string.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
// User
#include <cfg/cfg.h>
#include <def/uart.h>
#include <phy/uart.h>

// Hal Handler
UART_HandleTypeDef Phy_Uart_HalHandle;

// Queue Handler
QueueHandle_t Phy_Uart_Tx_QueueHandle;
QueueHandle_t Phy_Uart_Rx_QueueHandle;

// Task Handler
TaskHandle_t Phy_Uart_Tx_TaskHandle;
TaskHandle_t Phy_Uart_Rx_TaskHandle;

// DMA Hal Handler
static DMA_HandleTypeDef phy_uart_dma_tx_hal_handle;
static DMA_HandleTypeDef phy_uart_dma_rx_hal_handle;

// Queue Stack
static uint8_t phy_uart_tx_queue_stack[sizeof(Phy_Uart_Message) * PHY_UART_TX_QUEUE_SIZE];
static uint8_t phy_uart_rx_queue_stack[sizeof(Phy_Uart_Message) * PHY_UART_RX_QUEUE_SIZE];

// Queue Control
static StaticQueue_t phy_uart_tx_queue_control;
static StaticQueue_t phy_uart_rx_queue_control;

// Task Stack
static StackType_t phy_uart_tx_task_stack[PHY_UART_TX_STACK_SIZE];
static StackType_t phy_uart_rx_task_stack[PHY_UART_RX_STACK_SIZE];

// Task Control
static StaticTask_t phy_uart_tx_task_control;
static StaticTask_t phy_uart_rx_task_control;

// Initialize
void Phy_Uart_Init(void) {
  // Clear Global Variables
  Phy_Uart_Tx_QueueHandle = NULL;
  Phy_Uart_Rx_QueueHandle = NULL;
  Phy_Uart_Tx_TaskHandle  = NULL;
  Phy_Uart_Rx_TaskHandle  = NULL;
  memset(&Phy_Uart_HalHandle, 0, sizeof(Phy_Uart_HalHandle));

  // Clear Static Variables
  memset(&phy_uart_dma_tx_hal_handle, 0, sizeof(phy_uart_dma_tx_hal_handle));
  memset(&phy_uart_dma_rx_hal_handle, 0, sizeof(phy_uart_dma_rx_hal_handle));
  memset(&phy_uart_tx_queue_stack, 0x55, sizeof(phy_uart_tx_queue_stack));
  memset(&phy_uart_rx_queue_stack, 0x55, sizeof(phy_uart_rx_queue_stack));
  memset(&phy_uart_tx_queue_control, 0, sizeof(phy_uart_tx_queue_control));
  memset(&phy_uart_rx_queue_control, 0, sizeof(phy_uart_rx_queue_control));
  memset(&phy_uart_tx_task_stack, 0x55, sizeof(phy_uart_tx_task_stack));
  memset(&phy_uart_rx_task_stack, 0x55, sizeof(phy_uart_rx_task_stack));
  memset(&phy_uart_tx_task_control, 0, sizeof(phy_uart_tx_task_control));
  memset(&phy_uart_rx_task_control, 0, sizeof(phy_uart_rx_task_control));

  // Configure Peripheral
  Phy_Uart_HalHandle.Instance                    = PHY_UART_BASE;
  Phy_Uart_HalHandle.Init.BaudRate               = PHY_UART_BAUDRATE;
  Phy_Uart_HalHandle.Init.WordLength             = UART_WORDLENGTH_8B;
  Phy_Uart_HalHandle.Init.StopBits               = UART_STOPBITS_1;
  Phy_Uart_HalHandle.Init.Parity                 = UART_PARITY_NONE;
  Phy_Uart_HalHandle.Init.Mode                   = UART_MODE_TX_RX;
  Phy_Uart_HalHandle.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
  Phy_Uart_HalHandle.Init.OverSampling           = UART_OVERSAMPLING_8;
  Phy_Uart_HalHandle.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
  Phy_Uart_HalHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  // Reset Peripheral
  configASSERT(HAL_UART_DeInit(&Phy_Uart_HalHandle) == HAL_OK);

  // Init Peripheral
  configASSERT(HAL_UART_Init(&Phy_Uart_HalHandle) == HAL_OK);

  // Create Tx Queue
  configASSERT((Phy_Uart_Tx_QueueHandle = xQueueCreateStatic(
                    // Queue Size
                    PHY_UART_TX_QUEUE_SIZE,
                    // Item Size
                    sizeof(Phy_Uart_Message),
                    // Stack Area
                    phy_uart_tx_queue_stack,
                    // Control Block
                    &phy_uart_tx_queue_control)) != NULL);

  // Create Rx Queue
  configASSERT((Phy_Uart_Rx_QueueHandle = xQueueCreateStatic(
                    // Queue Size
                    PHY_UART_RX_QUEUE_SIZE,
                    // Item Size
                    sizeof(Phy_Uart_Message),
                    // Stack Area
                    phy_uart_rx_queue_stack,
                    // Control Block
                    &phy_uart_rx_queue_control)) != NULL);

  // Configure Tx Queue Name
  vQueueAddToRegistry(Phy_Uart_Tx_QueueHandle, "Phy/Uart/Tx/Queue");

  // Configure Rx Queue Name
  vQueueAddToRegistry(Phy_Uart_Rx_QueueHandle, "Phy/Uart/Rx/Queue");

  // Create Tx Task
  configASSERT((Phy_Uart_Tx_TaskHandle = xTaskCreateStatic(
                    // Function Pointer
                    Phy_Uart_Tx_Task,
                    // Task Name
                    "Phy/Uart/Tx/Task",
                    // Stack Size
                    PHY_UART_TX_STACK_SIZE,
                    // Task Parameter
                    NULL,
                    // Task Priority
                    PHY_UART_TX_TASK_PRIORITY,
                    // Stack Area
                    phy_uart_tx_task_stack,
                    // Control Block
                    &phy_uart_tx_task_control)) != NULL);

  // Create Rx Task
  configASSERT((Phy_Uart_Rx_TaskHandle = xTaskCreateStatic(
                    // Function Pointer
                    Phy_Uart_Rx_Task,
                    // Task Name
                    "Phy/Uart/Rx/Task",
                    // Stack Size
                    PHY_UART_RX_STACK_SIZE,
                    // Task Parameter
                    NULL,
                    // Task Priority
                    PHY_UART_RX_TASK_PRIORITY,
                    // Stack Area
                    phy_uart_rx_task_stack,
                    // Control Block
                    &phy_uart_rx_task_control)) != NULL);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
  GPIO_InitTypeDef GPIO_InitStruct;

  // Enable GPIO Tx/Rx Clock
  PHY_UART_TX_GPIO_CLK_ENABLE();
  PHY_UART_RX_GPIO_CLK_ENABLE();

  // Enable DMA Clock
  PHY_UART_DMA_CLK_ENABLE();

  // Enable Peripheral Clock
  PHY_UART_CLK_ENABLE();

  // Configure Common GPIO Struct
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  // Configure Tx GPIO
  GPIO_InitStruct.Pin       = PHY_UART_TX_GPIO_PIN;
  GPIO_InitStruct.Alternate = PHY_UART_TX_GPIO_AF;

  // Initialize Tx GPIO
  HAL_GPIO_Init(PHY_UART_TX_GPIO_PORT, &GPIO_InitStruct);

  // Configure Rx GPIO
  GPIO_InitStruct.Pin       = PHY_UART_RX_GPIO_PIN;
  GPIO_InitStruct.Alternate = PHY_UART_RX_GPIO_AF;

  // Initialize Rx GPIO
  HAL_GPIO_Init(PHY_UART_RX_GPIO_PORT, &GPIO_InitStruct);

  // Configure Tx DMA
  phy_uart_dma_tx_hal_handle.Instance                 = PHY_UART_DMA_TX_STREAM;
  phy_uart_dma_tx_hal_handle.Init.Channel             = PHY_UART_DMA_TX_CHANNEL;
  phy_uart_dma_tx_hal_handle.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  phy_uart_dma_tx_hal_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  phy_uart_dma_tx_hal_handle.Init.MemInc              = DMA_MINC_ENABLE;
  phy_uart_dma_tx_hal_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  phy_uart_dma_tx_hal_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  phy_uart_dma_tx_hal_handle.Init.Mode                = DMA_NORMAL;
  phy_uart_dma_tx_hal_handle.Init.Priority            = DMA_PRIORITY_LOW;

  // Configure Rx DMA
  phy_uart_dma_rx_hal_handle.Instance                 = PHY_UART_DMA_RX_STREAM;
  phy_uart_dma_rx_hal_handle.Init.Channel             = PHY_UART_DMA_RX_CHANNEL;
  phy_uart_dma_rx_hal_handle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  phy_uart_dma_rx_hal_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  phy_uart_dma_rx_hal_handle.Init.MemInc              = DMA_MINC_ENABLE;
  phy_uart_dma_rx_hal_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  phy_uart_dma_rx_hal_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  phy_uart_dma_rx_hal_handle.Init.Mode                = DMA_NORMAL;
  phy_uart_dma_rx_hal_handle.Init.Priority            = DMA_PRIORITY_HIGH;

  // Initialize DMA
  HAL_DMA_Init(&phy_uart_dma_tx_hal_handle);  // Tx
  HAL_DMA_Init(&phy_uart_dma_rx_hal_handle);  // Rx

  // Link DMA
  __HAL_LINKDMA(huart, hdmatx, phy_uart_dma_tx_hal_handle);  // Tx
  __HAL_LINKDMA(huart, hdmarx, phy_uart_dma_rx_hal_handle);  // Rx

  // Configure Interrupt
  HAL_NVIC_SetPriority(PHY_UART_DMA_TX_IRQn, PHY_UART_DMA_TX_NVIC_PRIORITY, 0);  // Tx DMA
  HAL_NVIC_SetPriority(PHY_UART_DMA_RX_IRQn, PHY_UART_DMA_RX_NVIC_PRIORITY, 0);  // Rx DMA
  HAL_NVIC_SetPriority(PHY_UART_IRQn, PHY_UART_NVIC_PRIORITY, 0);                // Peripheral

  // Enable Interrupt
  HAL_NVIC_EnableIRQ(PHY_UART_DMA_TX_IRQn);  // Tx DMA
  HAL_NVIC_EnableIRQ(PHY_UART_DMA_RX_IRQn);  // Rx DMA
  HAL_NVIC_EnableIRQ(PHY_UART_IRQn);         // Peripheral
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
  // Reset Peripheral
  PHY_UART_FORCE_RESET();
  PHY_UART_RELEASE_RESET();

  // Disable GPIO Clock
  HAL_GPIO_DeInit(PHY_UART_TX_GPIO_PORT, PHY_UART_TX_GPIO_PIN);  // Tx
  HAL_GPIO_DeInit(PHY_UART_RX_GPIO_PORT, PHY_UART_RX_GPIO_PIN);  // Rx

  // Disable Tx DMA
  if (huart->hdmatx != NULL) {
    HAL_DMA_DeInit(huart->hdmatx);
  }

  // Disable Rx DMA
  if (huart->hdmarx != NULL) {
    HAL_DMA_DeInit(huart->hdmarx);
  }

  // Disable Interrupt
  HAL_NVIC_DisableIRQ(PHY_UART_DMA_TX_IRQn);
  HAL_NVIC_DisableIRQ(PHY_UART_DMA_RX_IRQn);
}
