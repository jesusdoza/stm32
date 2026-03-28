#include "main.h"
#include "uart.h"
#include <stdio.h>

#define GPIOAEN (1u << 0) // enable clock for GPIOA
#define GPIOA_5 (1u << 5) // pin 5 of GPIOA

#define LED_PIN GPIOA_5

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
  while (1) {
    // printf("hello from print modular h bits cleared with binary \n\r");
    received_char = uart2_read();
    if (received_char == '1') {
      GPIOA->ODR |= LED_PIN; // set pin 5 (turn on LED)
    } else {
      GPIOA->ODR &= ~LED_PIN; // clear pin 5 (turn off LED)
    }
  }

  return 0;
}
