#include "main.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/_intsup.h>

uint32_t timestamp = 0;
// entry point
int main(void) {
  usart2_tx_init();
  tim2_pa5_output_compare();
  tim3_pa6_input_capture();
  while (1) {
    while (!(TIM3->SR & SR_CC1IF)) {
      // wait for capture of edge
    }

    // read cpature value from CCR1
    timestamp = TIM3->CCR1;
    // clear capture flag by writing 0 to it
    TIM3->SR &= ~SR_CC1IF;
    // print uart message
    printf("Captured timestamp: %lu \n\r", timestamp);
  }

  return 0;
}
