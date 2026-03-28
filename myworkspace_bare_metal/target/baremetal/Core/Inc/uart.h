#ifndef __UART_H
#define __UART_H
#endif // __UART_H

#include "stm32f446xx.h"
#include <stdint.h>

// prototypes
void usart2_tx_init(void);
void usart2_rxtx_init(void);
char uart2_read(void);
