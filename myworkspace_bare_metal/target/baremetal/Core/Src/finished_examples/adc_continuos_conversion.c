#include "main.h"
#include "adc.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

uint32_t sensor_value = 0;
// entry point
int main(void) {

  // usart2_tx_init();
  usart2_rxtx_init();

  // Initialize ADC on PA1
  pa1_init();
  startConversion();

  while (1) {
    sensor_value = adc_read();
    printf("sensor value: %d \n\r", (int)sensor_value);
  }

  return 0;
}
