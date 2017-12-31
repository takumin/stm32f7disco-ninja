// STM32F7HAL
#include <stm32f7xx.h>
// User
#include <def/macro.h>
#include <def/tim.h>
#include <phy/tim.h>

ITCM void PHY_TIM_1S_IRQ_HANDLER(void) {
  // Clear Interrupt Flag
  Phy_Tim_1s_HalHandle.Instance->SR = ~(TIM_IT_UPDATE);
  // 1Sec Global Variable
  Phy_Tim_1s_Counter++;
}

ITCM void PHY_TIM_1MS_IRQ_HANDLER(void) {
  // Clear Interrupt Flag
  Phy_Tim_1ms_HalHandle.Instance->SR = ~(TIM_IT_UPDATE);
  // STM32F7HAL Global Variable
  HAL_IncTick();
}
