#include "exti.h"

#define GPIOCEN (1U << 2) // GPIOC clock enable bit

#define SYSCFG_EN (1U << 14) // SYSCFG clock enable bit

void pc13_exti_init(void) {
  /*disable global interrupts*/ // to avoid any unwanted interrupts during the
                                // configuration

  __disable_irq();

  /*enable clock for GPIOC*/
  RCC->AHB1ENR |= GPIOCEN;

  /*enable syscfg clock*/
  RCC->APB2ENR |= SYSCFG_EN;
  /*select portC for exti13*/
  /*unmask EXTI13*/
  /*configure EXTI13 for falling edge trigger*/
  /*enable EXTI13 line in NVIC*/
  /*enable global interrupts*/
  __enable_irq();
}