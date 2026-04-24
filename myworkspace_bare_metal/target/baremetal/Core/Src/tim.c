#include "tim.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"

#define TIM2_EN (1u << 0)       // Enable clock for TIM2 (bit 0 in APB1ENR)
#define TIM3_EN (1u << 1)       // Enable clock for TIM3 (bit 1 in APB1ENR)
#define CR1_CEN (1u << 0)       // Counter enable bit in TIM2 control register 1
#define GPIOAEN (1u << 0)       // enable clock for GPIOA
#define AFR5_TIM (1u << 20)     // Alternate function 1 for pin 5 (TIM2_CH1)
#define AFR6_TIM (0b0010 << 24) // Alternate function 2 for pin 6 (TIM3_CH1)
#define OC_TOGGLE (0b011 << 4)

#define CCER_CC1S (0b01 << 0) // Capture/Compare 1 selection bits in TIM3 CCER
#define CCER_CC1E (1u << 0)   // Capture/Compare 1 enable bit in TIM3 CCER
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

void configPa6ForTimInput(void) {
  // enable clock to GPIOA
  RCC->AHB1ENR |= GPIOAEN;

  // pin 6 of GPIOA as alternate function mode
  GPIOA->MODER &=
      ~(0b11 << 12);            // clear pin a6 mode to 00 (input) / reset state
  GPIOA->MODER |= (0b10 << 12); // set pin 6 to alternate function mode

  // alternate function type to tim3 ch1 (AF2)
  GPIOA->AFR[0] |= AFR6_TIM; // set AFR6 to AF2 (TIM3_CH1)
}

void configTim3InputCapture(void) {
  // clock access to timer 2 bus
  RCC->APB1ENR |= TIM3_EN;

  // set prescaler value default 16MHz, we want 1Hz so we need to divide by
  // 16000 to get 1ms tick
  TIM3->PSC =
      16000 - 1; // Prescaler: 16000 counting from 0 to 15999. 16,000,000 /
                 // 16,000 = 1,000 ticks per second (1 tick = 1 ms)

  // set auto reload value
  TIM3->ARR =
      10000 - 1; // Auto-reload: 10,000 counting from 0 to 9999. 10,000 ticks
                 // per second means the timer will overflow every 1 second

  // enable input capture mode for channel 1, map it to TI1 (CC1S = 01)
  TIM3->CCMR1 |= CCER_CC1S; // Set CC1S bits to 01 for input capture mode
                            // enable tim3 ch1 in input capture mode

  TIM3->CCER |= CCER_CC1E; // Enable capture for channel 1 (CC1E bit in CCER)

  // // clear timer counter
  // TIM3->CNT = 0;

  // enable timer
  TIM3->CR1 |= CR1_CEN; // Enable TIM3
}

void tim3_pa6_input_capture(void) {

  configPa6ForTimInput();

  configTim3InputCapture();
}
