#include "main.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN (1u << 0) // enable clock for GPIOA
#define GPIOA_5 (1u << 5) // pin 5 of GPIOA
#define LED_PIN GPIOA_5

// entry point
int main(void) {

  // give clock access to GPIOA
  RCC->AHB1ENR |= GPIOAEN;
  // set pin 5 of GPIOA as output
  GPIOA->MODER &= ~(0b11 << 10); // clear pin 5 mode to 00 (input) / reset state
  GPIOA->MODER |= (0b01 << 10);  // set pin 5 mode to 01 (output)

  usart2_rxtx_init();

  while (1) {
    printf("a second has passed\n\r");
    GPIOA->ODR ^= LED_PIN; // toggle pin 5 (turn on/off LED)
    systickDelayMs(1000);
  }

  return 0;
}
