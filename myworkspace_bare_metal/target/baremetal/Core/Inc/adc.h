#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void pa1_init(void);
void startConversion(void);
uint32_t adc_read(void);

#endif /* ADC_H */
