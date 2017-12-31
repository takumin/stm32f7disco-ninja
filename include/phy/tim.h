#ifndef PHY_TIM_H
#define PHY_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

// STM32F7HAL
#include <stm32f7xx.h>
// User
#include <def/tim.h>

// HAL Handler
extern TIM_HandleTypeDef Phy_Tim_1s_HalHandle;
extern TIM_HandleTypeDef Phy_Tim_1ms_HalHandle;
extern TIM_HandleTypeDef Phy_Tim_100us_HalHandle;

// 1Sec Timer Counter
extern volatile uint32_t Phy_Tim_1s_Counter;

// Initialize
extern void Phy_Tim_Init(void);

// Interrupt 1Sec
extern void PHY_TIM_1S_IRQ_HANDLER(void);

// Interrupt 1ms
extern void PHY_TIM_1MS_IRQ_HANDLER(void);

// Get 1Sec Timer Counter
static inline uint32_t Phy_Tim_Get_1s_Timer(void) {
  return Phy_Tim_1s_Counter;
}

// Get 1Sec Tick Counter
static inline uint32_t Phy_Tim_Get_1s_Tick(void) {
  return Phy_Tim_1s_HalHandle.Instance->CNT;
}

// Get 100us Tick Counter
static inline uint16_t Phy_Tim_Get_100us_Tick(void) {
  return (uint16_t)(Phy_Tim_100us_HalHandle.Instance->CNT);
}

#ifdef __cplusplus
}
#endif

#endif  // PHY_TIM_H
