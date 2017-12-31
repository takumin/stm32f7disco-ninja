// STDC
#include <string.h>
// STM32F7HAL
#include <stm32f7xx_ll_bus.h>
#include <stm32f7xx_ll_cortex.h>
#include <stm32f7xx_ll_pwr.h>
#include <stm32f7xx_ll_rcc.h>
#include <stm32f7xx_ll_utils.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <svc/init.h>

//
// External Function Prototypes
//
extern void _start(void);

//
// Internal Function Prototypes
//
static inline void NVIC_Config(void);
static inline void MPU_Config(void);
static inline void CPU_CACHE_Enable(void);
static inline void SystemClock_Config(void);

//
// Program Entry Point
//
void _start(void) {
  // NVIC Interrupt Configuration
  NVIC_Config();

  // MPU Region Configuration
  MPU_Config();

  // CPU Cache Enable
  CPU_CACHE_Enable();

  // CPU Clock Configuration
  SystemClock_Config();

  // Initialize Handler
  Svc_Init_Startup();

  // Start FreeRTOS Kernel
  vTaskStartScheduler();
}

//
// NVIC Interrupt Configuration
//
static inline void NVIC_Config(void) {
  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

//
// MPU Region Configuration
//
static inline void MPU_Config(void) {
  // Disable MPU
  LL_MPU_Disable();

  // Configure SRAM1/SRAM2
  LL_MPU_ConfigRegion(
      LL_MPU_REGION_NUMBER0, 0x00, 0x20010000UL,
      LL_MPU_REGION_SIZE_256KB | LL_MPU_REGION_FULL_ACCESS | LL_MPU_ACCESS_NOT_BUFFERABLE | LL_MPU_ACCESS_CACHEABLE | LL_MPU_ACCESS_SHAREABLE | LL_MPU_TEX_LEVEL0 | LL_MPU_INSTRUCTION_ACCESS_ENABLE);

  // Enable MPU
  LL_MPU_Enable(LL_MPU_CTRL_PRIVILEGED_DEFAULT);
}

//
// CPU Cache Enable
//
static inline void CPU_CACHE_Enable(void) {
  // Enable I-Cache
  SCB_EnableICache();

  // Enable D-Cache
  SCB_EnableDCache();
}

//
// CPU Clock Configuration
//
static inline void SystemClock_Config(void) {
  LL_UTILS_PLLInitTypeDef pll_init = {
      .PLLM = LL_RCC_PLLM_DIV_25,
      .PLLN = 432,
      .PLLP = LL_RCC_PLLP_DIV_2,
  };
  LL_UTILS_ClkInitTypeDef clk_init = {
      .AHBCLKDivider  = LL_RCC_SYSCLK_DIV_1,
      .APB1CLKDivider = LL_RCC_APB1_DIV_4,
      .APB2CLKDivider = LL_RCC_APB2_DIV_2,
  };
  LL_RCC_ClocksTypeDef clk_freq;

  // Configure Clock
  LL_PLL_ConfigSystemClock_HSE(HSE_VALUE, LL_UTILS_HSEBYPASS_OFF, &pll_init, &clk_init);

  // Get Clock
  LL_RCC_GetSystemClocksFreq(&clk_freq);

  // Update CMSIS Variable
  SystemCoreClock = clk_freq.SYSCLK_Frequency;

  // Configure SysTick
  LL_Init1msTick(clk_freq.HCLK_Frequency);

  // Configure SysTick IRQ Priority
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), TICK_INT_PRIORITY, 0));
}
