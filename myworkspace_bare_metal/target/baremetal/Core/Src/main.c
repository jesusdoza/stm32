#include "main.h"
#include "adc.h"
#include "uart.h"
#include <stdio.h>

volatile char received_char;
// entry point
int main(void) {
  // give clock access to GPIOA
  RCC->AHB1ENR |= GPIOAEN;

  // set pin 5 of GPIOA as output
  GPIOA->MODER &= ~(0b11 << 10); // clear pin 5 mode to 00 (input) / reset state
  GPIOA->MODER |= (0b01 << 10);  // set pin 5 mode to 01 (output)

  // usart2_tx_init();
  usart2_rxtx_init();

  // Initialize ADC on PA1
  pa1_init();

  char msg[64];
  uint32_t adc_value;
  while (1) {
  }

  return 0;
}
