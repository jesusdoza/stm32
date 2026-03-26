#include "main.h"
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN (1U << 0)
#define USART2EN (1U << 17)

#define CR1_TE (1U << 3) // usart CR1 transmitter enable
#define CR1_UE = (1u << 13)

#define SYS_FREQ 160000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

int main(void) {

  /*
  usart2 pins
  PA2 TX
  PA3 RX
  AF7 alternat function

  */

  while (1) {
  }
}

void usart2_tx_init(void) {
  /*enable clock to GPIOA*/
  RCC->AHB1ENR |= GPIOAEN;
  /*config usart pins*/
  // set PA2 to alternate function mode
  GPIOA->MODER &= ~(0b11 << 4); // clear bits first space
  GPIOA->MODER |= (0b10 << 4);  // then activate bits space

  // set PA3
  GPIOA->MODER &= ~(0b11 << 6); // clear bits first space
  GPIOA->MODER |= (0b10 << 6);  // then activate bits space

  // set PA2 alternate function to UART_tx AF07
  GPIOA->MODER &= ~(0b1111 << 8); // clear bits first space
  GPIOA->AFR[0] |= (0b0111 << 8);

  // set PA3 alternate function to UART_rx AF7
  GPIOA->MODER &= ~(0b1111 << 12); // clear bits first space
  GPIOA->AFR[0] |= (0b0111 << 12);

  // config uart

  // configure uart module clock access
  RCC->APB1ENR |= USART2EN;

  // config uart baudrate

  uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE)

      // config transfer direction
      USART2->CR1 = CR1_TE;
  USART2->CR1 = CR1_UE;

  // enable uart module
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate) {
  USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {

  return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}
