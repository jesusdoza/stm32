#include "systick.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL 16000
#define CTRL_ENABLE (1U << 0)
#define CTRL_CLKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)

void systickDelayMs(int n) {
  // configure systick

  // reload with number of clocks per millisecond
  SysTick->LOAD = SYSTICK_LOAD_VAL; // 16000

  // clear systick current value register
  SysTick->VAL = 0; // clear current value register

  // enable systick and select internal clock source
  SysTick->CTRL =
      CTRL_ENABLE |
      CTRL_CLKSRC; // enable systick and select internal clock source

  for (int i = 0; i < n; i++) {
    // wait until count flag is set indicating the timer has counted down to
    // zero
    while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {
      // wait
    }
  }
  SysTick->CTRL = 0; // disable systick

  //
}