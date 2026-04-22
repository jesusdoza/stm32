#include "tim.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"

#define TIM2_EN (1u << 0)   // Enable clock for TIM2 (bit 0 in APB1ENR)
#define CR1_CEN (1u << 0)   // Counter enable bit in TIM2 control register 1
#define GPIOAEN (1u << 0)   // enable clock for GPIOA
#define AFR5_TIM (1u << 20) // Alternate function 1 for pin 5 (TIM2_CH1)
#define OC_TOGGLE (0b011 << 4)

#define TIM2_CC1E (1u << 0) // Capture/Compare 1 output enable bit in TIM2 CCER

void configPa5ForTimOutput(void) {
  // enable clock to GPIOA
  RCC->AHB1ENR |= GPIOAEN;

  // pin 5 of GPIOA as alternate function mode
  GPIOA->MODER &= ~(1u << 10); // clear pin 5 mode to 00 (input) / reset state
  GPIOA->MODER |= (1u << 11);  // set pin 5 to alternate function mode

  // alternate function type to tim2 ch1 (AF1)
  GPIOA->AFR[0] |= AFR5_TIM;
}

void configTim2OutputRegister(void) {
  // clock access to timer 2 bus
  RCC->APB1ENR |= TIM2_EN;

  // set prescaler value default 16MHz, we want 1Hz so we need to divide by
  // 16000 to get 1ms tick
  TIM2->PSC = 1600 - 1; // Prescaler: 1600 counting from 0 to 1599. 16,000,000 /
                        // 1,600 = 10,000 ticks per second (1 tick = 0.1 ms)

  // set auto reload value
  TIM2->ARR =
      10000 - 1; // Auto-reload: 10,000 counting from 0 to 9999. 10,000 ticks
                 // per second means the timer will overflow every 1 second

  // set output compare mode for channel 1 to toggle on match
  TIM2->CCMR1 |= OC_TOGGLE; // Set OC1M bits to 011 for toggle mode
                            // enable tim2 ch1 in compare mode

  TIM2->CCER |= TIM2_CC1E; // Enable capture/compare output for channel 1

  // clear timer counter
  TIM2->CNT = 0;

  // enable timer
  TIM2->CR1 |= CR1_CEN; // Enable TIM2
}

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

void tim2_pa5_output_compare(void) {

  configPa5ForTimOutput();

  configTim2OutputRegister();
}
