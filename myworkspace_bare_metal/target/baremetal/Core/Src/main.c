#include "main.h"
#include "uart.h"
#include <stdio.h>

// entry point
int main(void) {

  usart2_tx_init();

  while (1) {
    printf("hello from print modular h includes RELOAD \n\r");
  }

  return 0;
}
