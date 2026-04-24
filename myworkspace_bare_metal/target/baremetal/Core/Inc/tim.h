#ifndef TIM_H
#define TIM_H

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#define SR_UIF (1u << 0)   // Update interrupt flag
#define SR_CC1IF (1u << 1) // Capture/Compare 1 interrupt flag
#endif                     /* TIM_H */
