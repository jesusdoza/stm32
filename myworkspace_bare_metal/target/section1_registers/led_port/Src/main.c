// turn on led PA5
// Port:A
// Pin:5

#include <stdio.h>
#define PERIPH_BASE              (0x40000000UL) // all periph begin at
#define AHB1_OFFSET              (0x00020000)
#define AHB1_PERIPH_BASE         (PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_OFFSET             (0x0UL) //its first address of base

#define GPIOA_BASE               (AHB1_PERIPH_BASE + GPIOA_OFFSET) //its first address of base


#define RCC_OFFSET               (0x3800UL) //rcc reseting clock control
#define RCC_BASE                 (PERIPH_BASE + RCC_OFFSET)

// actual pin address
#define RCC_AHB1ENR_OFFSET       (0x30UL)
#define RCC_AHB1EN_REGISTER              (*(volatile unsigned int *) (RCC_BASE + RCC_AHB1_OFFSET)) //register


// RCC 
#define GPIOAEN                              (1UL<<0) // shift 0x1UL to position 0 

//set mode or pin in register for port A
#define GPIOA_MODE_R_OFFSET                   (0x00UL)
#define GPIOA_MODE_REGISTER                       (*(volatile unsigned int *) ( GPIOA_BASE + GPIOA_MODE_R_OFFSET)) //register for mode

#define GPIOA_MODE_OUTPUT                    (01UL<<10) // mode general purpose shift 01 to position 10
//

#define GPIOA_ODR_OFFSET                      (0x14UL) //data ouput register for port GPIOA
#define GPIOA_OD_REGISTER                     (*(volatile unsigned int *) (GPIOA_BASE +  GPIOA_ODR_OFFSET)) //register output data where pin5 is


//set output data to pin 5
#define PIN5        (1U<<5)
#define LED_PIN     PIN5

// (1UL<<10) //set pin 10 to 1
// &=~(1UL <<11) // set bit 11 and only 11 to 0 zero

int main(){
    printf("start");
    return 0;
}
