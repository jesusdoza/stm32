#include "adc.h"
#include "stm32f446xx.h"

#define GPIOAEN (1U << 0)     // Bit 0: GPIOA clock enable
#define APB2_ADC1EN (1U << 8) // Bit 8: ADC1 clock enable
#define ADC_CH1 (1U << 0)     // ADC channel 1 corresponds to PA1
#define ADC_SEQ_LEN_1 (0x00)
#define CR2_ADON (1U << 0)       // Bit 0: ADC on/off
#define CR2_SWSTART (1U << 30)   // Bit 30: Start conversion of regular channels
#define ADC_SR_EOC_BIT (1U << 1) // Bit 1: End of conversion flag

void pa1_init(void) {
  // enable clock access to GPIOA
  RCC->APB2ENR |= GPIOAEN;

  // config pin PA1 as analog input
  GPIOA->MODER |= (1U << 2); // Clear mode bits for PA1
  GPIOA->MODER |= (1U << 3); // Set PA1 to analog mode

  RCC->APB2ENR |= APB2_ADC1EN;

  // conversion sequence start from channel 1 (PA1)
  ADC1->SQR3 = ADC_CH1; // conversion sequence length

  // conversion sequence length is 1 (only one channel)
  ADC1->SQR1 = (ADC_SEQ_LEN_1); // Set sequence length to 1

  // enable adc module
  ADC1->CR2 |= CR2_ADON;
}

void startConversion(void) {
  // start conversion of regular channels
  ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void) {

  // wait for conversion to be complete

  while (!(ADC1->SR & ADC_SR_EOC_BIT)) {
    // wait until the EOC (End of Conversion) flag is set
  }

  // read converted result
  return ADC1->DR;
}