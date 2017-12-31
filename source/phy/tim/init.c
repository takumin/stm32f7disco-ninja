// STDC
#include <stdint.h>
#include <string.h>
// STM32F7HAL
#include <stm32f7xx.h>
// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// User
#include <cfg/cfg.h>
#include <def/tim.h>
#include <phy/tim.h>

// HAL Handler
TIM_HandleTypeDef Phy_Tim_1s_HalHandle;
TIM_HandleTypeDef Phy_Tim_1ms_HalHandle;
TIM_HandleTypeDef Phy_Tim_100us_HalHandle;

// 1Sec Timer Counter
volatile uint32_t Phy_Tim_1s_Counter;

// Initialize
void Phy_Tim_Init(void) {
  // Clear Global Variables
  memset(&Phy_Tim_1s_HalHandle, 0, sizeof(Phy_Tim_1s_HalHandle));
  memset(&Phy_Tim_1ms_HalHandle, 0, sizeof(Phy_Tim_1ms_HalHandle));
  memset(&Phy_Tim_100us_HalHandle, 0, sizeof(Phy_Tim_100us_HalHandle));
  Phy_Tim_1s_Counter = 0;

  // Timer Clock == HCLK
  __HAL_RCC_TIMCLKPRESCALER(RCC_TIMPRES_ACTIVATED);

  // Configure Interrupt 1s Timer Peripheral
  Phy_Tim_1s_HalHandle.Instance               = PHY_TIM_1S_BASE;
  Phy_Tim_1s_HalHandle.Init.Period            = SystemCoreClock - 1U;
  Phy_Tim_1s_HalHandle.Init.Prescaler         = 0U;
  Phy_Tim_1s_HalHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  Phy_Tim_1s_HalHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  Phy_Tim_1s_HalHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  // Configure Interrupt 1ms Timer Peripheral
  Phy_Tim_1ms_HalHandle.Instance               = PHY_TIM_1MS_BASE;
  Phy_Tim_1ms_HalHandle.Init.Period            = 1000U - 1U;
  Phy_Tim_1ms_HalHandle.Init.Prescaler         = (SystemCoreClock / 1000) - 1U;
  Phy_Tim_1ms_HalHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  Phy_Tim_1ms_HalHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  Phy_Tim_1ms_HalHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  // Configure Free Run 100us Timer Peripheral
  Phy_Tim_100us_HalHandle.Instance               = PHY_TIM_100US_BASE;
  Phy_Tim_100us_HalHandle.Init.Period            = UINT16_MAX - 1U;
  Phy_Tim_100us_HalHandle.Init.Prescaler         = (SystemCoreClock / 10000) - 1U;
  Phy_Tim_100us_HalHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  Phy_Tim_100us_HalHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  Phy_Tim_100us_HalHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  // Initialize Interrupt 1s Timer Peripheral
  configASSERT((HAL_TIM_Base_Init(&Phy_Tim_1s_HalHandle)) == HAL_OK);

  // Initialize Interrupt 1ms Timer Initialize
  configASSERT((HAL_TIM_Base_Init(&Phy_Tim_1ms_HalHandle)) == HAL_OK);

  // Initialize Free Run 100us Timer Peripheral
  configASSERT((HAL_TIM_Base_Init(&Phy_Tim_100us_HalHandle)) == HAL_OK);

  // Configure NVIC Interrupt
  HAL_NVIC_SetPriority(PHY_TIM_1S_IRQ_NUMBER, PHY_TIM_1S_NVIC_PRIORITY, 0);
  HAL_NVIC_SetPriority(PHY_TIM_1MS_IRQ_NUMBER, PHY_TIM_1MS_NVIC_PRIORITY, 0);

  // Enable NVIC Interrupt
  HAL_NVIC_EnableIRQ(PHY_TIM_1S_IRQ_NUMBER);
  HAL_NVIC_EnableIRQ(PHY_TIM_1MS_IRQ_NUMBER);

  // Clear Counter
  Phy_Tim_1s_HalHandle.Instance->CNT    = 0UL;
  Phy_Tim_1ms_HalHandle.Instance->CNT   = 0UL;
  Phy_Tim_100us_HalHandle.Instance->CNT = 0UL;

  // Clear Status
  Phy_Tim_1s_HalHandle.Instance->SR    = 0UL;
  Phy_Tim_1ms_HalHandle.Instance->SR   = 0UL;
  Phy_Tim_100us_HalHandle.Instance->SR = 0UL;

  // Start Interrupt 1s Timer Peripheral
  configASSERT((HAL_TIM_Base_Start_IT(&Phy_Tim_1s_HalHandle)) == HAL_OK);

  // Start Interrupt 1ms Timer Peripheral
  configASSERT((HAL_TIM_Base_Start_IT(&Phy_Tim_1ms_HalHandle)) == HAL_OK);

  // Start Free Run 100us Timer Peripheral
  configASSERT((HAL_TIM_Base_Start(&Phy_Tim_100us_HalHandle)) == HAL_OK);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {
  if (htim->Instance == PHY_TIM_1S_BASE) {
    // Enable Clock
    PHY_TIM_1S_CLK_ENABLE();
  } else if (htim->Instance == PHY_TIM_1MS_BASE) {
    // Enable Clock
    PHY_TIM_1MS_CLK_ENABLE();
  } else if (htim->Instance == PHY_TIM_100US_BASE) {
    // Enable Clock
    PHY_TIM_100US_CLK_ENABLE();
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim) {
  if (htim->Instance == PHY_TIM_1S_BASE) {
    // Reset Clock
    PHY_TIM_1S_FORCE_RESET();
    PHY_TIM_1S_RELEASE_RESET();

    // Disable Clock
    PHY_TIM_1S_CLK_DISABLE();
  } else if (htim->Instance == PHY_TIM_1MS_BASE) {
    // Reset Clock
    PHY_TIM_1MS_FORCE_RESET();
    PHY_TIM_1MS_RELEASE_RESET();

    // Disable Clock
    PHY_TIM_1MS_CLK_DISABLE();
  } else if (htim->Instance == PHY_TIM_100US_BASE) {
    // Reset Clock
    PHY_TIM_100US_FORCE_RESET();
    PHY_TIM_100US_RELEASE_RESET();

    // Disable Clock
    PHY_TIM_100US_CLK_DISABLE();
  }
}

void HAL_SuspendTick(void) {
  __HAL_TIM_DISABLE_IT(&Phy_Tim_1ms_HalHandle, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void) {
  __HAL_TIM_ENABLE_IT(&Phy_Tim_1ms_HalHandle, TIM_IT_UPDATE);
}
