#include "main.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

// entry point
int main(void) {
  tim2_pa5_output_compare();

  while (1) {
  }

  return 0;
}
