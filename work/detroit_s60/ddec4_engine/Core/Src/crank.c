#include "crank.h"
#include "stm32f446xx.h"

#define CRANK_PIN (16) // bit position for PC8

// Initialize crank signal generation
void initCrankPin() {
  // Enable clock for GPIOC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Clear and set PC8 as alternate function mode
  GPIOC->MODER &= ~(0b11 << CRANK_PIN);
  GPIOC->MODER |= (0b10 << CRANK_PIN); // Set PC8 as alternate function mode

  // Clear and set alternate function for PC8 to AF2 (TIM3)
  GPIOC->AFR[1] &= ~(0b1111 << 0);
  GPIOC->AFR[1] |=
      (0b0010 << 0); // Set alternate function for pin PC8 to AF2 (TIM3)
}

// Initialize timer for crank signal generation
void initCrankTimer() {
  // Enable clock for TIM3
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  // Set TIM3 prescaler and auto-reload for 1 second period
  TIM3->PSC = 8399; // Prescaler value (PSC + 1) = 8400, so 84MHz / 8400 = 10kHz
  TIM3->ARR =
      10000 -
      1; // Auto-reload value for 1 second interval (10kHz / 10,000 = 1Hz)

  // Set TIM3 channel 1 to toggle mode
  TIM3->CCMR1 |= (0b11 << 4); // Set OC1M to toggle mode
  // Clear TIM3 counter
  TIM3->CNT = 0;
}

// Enable the crank timer
void enableCrankTimer() { TIM3->CR1 |= TIM_CR1_CEN; }

// Set the timer auto-reload value to adjust the crank signal frequency
void updateTimer(int value) {

  // disbale timer
  TIM3->CR1 &= ~TIM_CR1_CEN; // Disable TIM3

  // update timer value
  TIM3->ARR = value - 1; // Set auto-reload value for the timer

  // Clear timer counter
  TIM3->CNT = 0;

  // reset timer
  TIM3->EGR |= TIM_EGR_UG; // Generate an update event to reset the timer
}

void start() {
  initCrankPin();
  initCrankTimer();
  enableCrankTimer();
}