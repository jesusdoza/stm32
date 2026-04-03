#include "adc.h"
#include "stm32f446xx.h"

#define APB2_ADC1EN (1U << 8) // Bit 8: ADC1 clock enable
#define GPIOAEN (1U << 0)     // Bit 0: GPIOA clock enable
#define PA1 (1U << 1)         // Bit 1: PA1 pin

void pa1_init(void) {

  // config pin PA1 as analog input
  GPIOAEN->MODER &= ~(0b11 << 2); // Clear mode bits for PA1
  GPIOAEN->MODER |= (0b11 << 2);  // Set PA1 to analog mode

  // enable clock access to GPIOA
  RCC->APB2ENR |= GPIOAEN;
}