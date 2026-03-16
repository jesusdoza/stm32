/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f446xx.h"


#define GPIOAEN		(1U<<0)
#define GPOICEN   	(1U<<2)
#define PIN5		(1U<<5)
#define PIN13		(1U<<13)
#define LED_PIN 	PIN5
#define BTN_PIN PIN13

int main(void){

//enable clock on port C and A
RCC->AHB1ENR |= GPIOAEN;
RCC->AHB1ENR |= GPOICEN;

//set PA5 output pin
GPIOA->MODER |= (1U<<10);
GPIOA->MODER &=~(1U<<11);

// set PC13 input pin
GPIOC->MODER &=~(0b11<<26);


	while(1){

		//check if btn is pressed
		 if(GPIOC->IDR & BTN_PIN){
			GPIOA->BSRR |= LED_PIN;
//			for ( i = 0;  i < 1000000; ++ i) {}

		 }else{

				GPIOA->BSRR |= (1UL<<21);


		 }

	}
}
