// turn on led PA5
// Port:A
// Pin:5

#include <stdio.h>
#define PERIPH_BASE         (0x40000000UL) // all periph begin at
#define AHB1_OFFSET         (0x00020000)
#define AHB1_PERIPH_BASE     (PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_OFFSET        (0x0UL) //its first address of base
#define GPIOA_BASE        (AHB1_PERIPH_BASE + GPIOA_OFFSET) //its first address of base







int main(){
    printf("start");
    return 0;
}
