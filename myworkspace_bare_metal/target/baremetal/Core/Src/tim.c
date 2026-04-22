#include "tim.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"

#define TIM2_EN (1u << 0) // Enable clock for TIM2 (bit 0 in APB1ENR)
#define CR1_CEN (1u << 0) // Counter enable bit in TIM2 control register 1

void tim2_1hz_init(void) {

  // enable clock access to timer 2 bus
  RCC->APB1ENR |= TIM2_EN;

  // set prescaler value default 16MHz, we want 1Hz so we need to divide by
  // 16000 to get 1ms tick
  TIM2->PSC = 1600 - 1; // Prescaler: 1600 counting from 0 to 1599. 16,000,000 /
                        // 1,600 = 10,000 ticks per second (1 tick = 0.1 ms)

  // set auto reload value
  TIM2->ARR =
      10000 - 1; // Auto-reload: 10,000 counting from 0 to 9999. 10,000 ticks
                 // per second means the timer will overflow every 1 second

  // clear timer counter
  TIM2->CNT = 0;

  // enable timer
  TIM2->CR1 |= CR1_CEN; // Enable TIM2
}