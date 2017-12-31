#ifndef DEF_LED_H
#define DEF_LED_H

#ifdef __cplusplus
extern "C" {
#endif

// STM32F7HAL
#include <stm32f7xx.h>

// GPIO Clock Enable
#define PHY_LED1_GPIO_CLK_ENABLE() __HAL_RCC_GPIOI_CLK_ENABLE()

// GPIO Port
#define PHY_LED1_GPIO_PORT GPIOI

// GPIO Pin
#define PHY_LED1_GPIO_PIN GPIO_PIN_1

#ifdef __cplusplus
}
#endif

#endif  // DEF_LED_H
