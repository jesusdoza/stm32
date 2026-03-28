#include "uart.h"
#include <stdint.h>
#include <stdio.h>

// ports enable
#define GPIOAEN (1U << 0)
#define USART2EN (1U << 17)

// usart control registers
#define CR1_TE (1U << 3)  // usart CR1 transmitter enable
#define CR1_RE (1U << 2)  // usart CR1 receiver enable
#define CR1_UE (1U << 13) // usart enable
#define SR_TXE (1U << 7)  // USART SR Transmiter empty status register
#define SR_RXNE (1U << 5) // USART SR Receiver not empty status register

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

// // prototypes
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

// void usart2_tx_init(void);
void uart2_write(int ch);

// IMPLEMENTATIONS *******************************************************

// new for both tx and rx
void usart2_rxtx_init(void) {
  /*enable clock to GPIOA*/
  RCC->AHB1ENR |= GPIOAEN;
  /*config usart pins*/
  // set PA2 to alternate function mode (bits 5:4 = 10)
  GPIOA->MODER &= ~(0b11 << 4); // clear both bits 5:4
  GPIOA->MODER |= (0b10 << 4);  // set to 10 (alternate function)

  // set PA2 alternate function to UART_tx AF07
  GPIOA->AFR[0] &= ~(0b1111 << 8);
  GPIOA->AFR[0] |= (0b0111 << 8);

  //  set PA3 to alternate function mode (bits 5:4 = 10)
  GPIOA->MODER &= ~(0b11 << 6); // clear both bits 5:4
  GPIOA->MODER |= (0b10 << 6);  // set to 10 (alternate function)

  //  set PA3 alternate function to UART_rx AF07
  GPIOA->AFR[0] &= ~(0b1111 << 12);
  GPIOA->AFR[0] |= (0b0111 << 12);

  // configure uart module clock access
  RCC->APB1ENR |= USART2EN;

  // config uart baudrate
  uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

  // config transfer direction
  USART2->CR1 |= CR1_TE | CR1_RE; // enable transmitter and receiver

  USART2->CR1 |= CR1_UE; // enable uart module

  return;
}

// old only for tx
void usart2_tx_init(void) {
  /*enable clock to GPIOA*/
  RCC->AHB1ENR |= GPIOAEN;
  /*config usart pins*/
  // set PA2 to alternate function mode (bits 5:4 = 10)
  GPIOA->MODER &= ~(0b11 << 4); // clear both bits 5:4
  GPIOA->MODER |= (0b10 << 4);  // set to 10 (alternate function)

  // set PA2 alternate function to UART_tx AF07
  GPIOA->AFR[0] &= ~(0b1111 << 8);
  GPIOA->AFR[0] |= (0b0111 << 8);

  // configure uart module clock access
  RCC->APB1ENR |= USART2EN;

  // config uart baudrate

  uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

  // config transfer directio
  USART2->CR1 = CR1_TE;
  USART2->CR1 |= CR1_UE;

  // enable uart module
  return;
}

void uart2_write(int ch) {
  // make user transmit data register is empty before writing to it
  // check the status of the transmit data register empty flag in the USART_SR
  // register before writing to the USART_DR register
  while (!(USART2->SR & SR_TXE)) {
    // wait
  }
  USART2->DR = (ch & 0xFF); // write character in the 8 bit data register
  return;
}

char uart2_read(void) {
  // wait until the receive data register is not empty no need to read if empty
  // while (!(USART2->SR & SR_RXNE)) {
  //   // wait
  // }

  return USART2->DR; // read the received data from the data register
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {

  return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate) {
  USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);

  return;
}

int __io_putchar(int ch) {
  uart2_write(ch);
  return ch;
}