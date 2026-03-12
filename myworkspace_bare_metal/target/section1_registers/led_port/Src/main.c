// turn on led PA5
// Port:A
// Pin:5

#include <stdio.h>
#define PERIPH_BASE              (0x40000000UL) // all periph begin at
#define AHB1_OFFSET              (0x00020000UL)
#define AHB1_PERIPH_BASE         (PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_OFFSET             (0x0UL) //its first address of base

#define GPIOA_BASE               (AHB1_PERIPH_BASE + GPIOA_OFFSET) //its first address of base
// #define GPIOA_BASE               ( PERIPH_BASE + GPIOA_OFFSET) //its first address of base


#define RCC_OFFSET               (0x3800UL) 
#define RCC_BASE                 (AHB1_PERIPH_BASE + RCC_OFFSET)//starting address 

// actual pin address
#define RCC_AHB1ENR_OFFSET       (0x30UL) // offset to target register for AHB1 bus
#define RCC_AHB1EN_REGISTER              (*(volatile unsigned int *) (RCC_BASE + RCC_AHB1ENR_OFFSET)) //register to target for our PORT

// RCC 
#define GPIOAEN                              (1U<<0) // shift 0x1UL to position 0  //this is port a enable the clock on this port 

//set mode or pin in register for port A
#define GPIOA_MODE_R_OFFSET                   (0x00UL) // target port mode register for port AT offset
#define GPIOA_MODE_REGISTER                       (*(volatile unsigned int *) ( GPIOA_BASE + GPIOA_MODE_R_OFFSET)) //register for mode

//

#define GPIOA_ODR_OFFSET                      (0x14UL) //data ouput register for port GPIOA
#define GPIOA_OD_REGISTER                     (*(volatile unsigned int *) (GPIOA_BASE +  GPIOA_ODR_OFFSET)) //register output data where pin5 is


//set output data to pin 5
#define PIN5        (1U<<5)
#define LED_PIN     PIN5

// (1UL<<10) //set pin 10 to 1
// &=~(1UL <<11) // set bit 11 and only 11 to 0 zero

int main(){
   //enable clock access to register for pin
   RCC_AHB1EN_REGISTER |= GPIOAEN;

   //set PA5 mode as output pin uses bits 10 and 11
   GPIOA_MODE_REGISTER |= (1UL << 10); //set bit 10 to 1
   GPIOA_MODE_REGISTER &=~(1UL <<11); // set bit 11 and only 11 to 0 zero

 while (1) {
    GPIOA_OD_REGISTER|=LED_PIN;
 }

}
