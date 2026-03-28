#include "main.h"
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>

// ports enable
#define GPIOAEN (1U << 0)
#define USART2EN (1U << 17)

// usart control registers
#define CR1_TE (1U << 3)  // usart CR1 transmitter enable
#define CR1_UE (1U << 13) // usart enable
#define SR_TXE (1U << 7)  // USART SR Transmiter empty status register

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

// prototypes
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void usart2_tx_init(void);
void uart2_write(int ch);

// retargeting printf to uart2 aka implementing __io_putchar
int __io_putchar(int ch) {
  uart2_write(ch);
  return ch;
}

// entry point
int main(void) {

  usart2_tx_init();

  while (1) {
    printf("hello from print 123 \n\r");
  }
}

void usart2_tx_init(void) {
  /*enable clock to GPIOA*/
  RCC->AHB1ENR |= GPIOAEN;
  /*config usart pins*/
  // set PA2 to alternate function mode (bits 5:4 = 10)
  GPIOA->MODER &= ~(3U << 4); // clear both bits 5:4
  GPIOA->MODER |= (2U << 4);  // set to 10 (alternate function)

  // set PA2 alternate function to UART_tx AF07
  GPIOA->AFR[0] |= (1U << 8);
  GPIOA->AFR[0] |= (1U << 9);
  GPIOA->AFR[0] |= (1U << 10);
  GPIOA->AFR[0] &= ~(1U << 11);

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

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,
                              uint32_t BaudRate) {
  USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);

  return;
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {

  return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

void uart2_write(int ch) {
  // make user transmit data register is empty before writing to it
  // wait until transmit data register is empty
  // check the status of the transmit data register empty flag in the USART_SR
  // register before writing to the USART_DR register
  // wait until transmit data register is empty
  while (!(USART2->SR & SR_TXE)) {
    // wait
  }
  USART2->DR = (ch & 0xFF); // write character in the 8 bit data register
  return;
}
