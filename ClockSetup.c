#include "ClockSetup.h"
#include "PinSetup.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

uint8_t clock_buffer[BufferSize];
//
// Sets up the TIM2 clock
// And GPIOA pin 3 with ALT function set to AF1
// Clock is set up to look for input on chanel 1
void clock_setup(void){
	
	//pin_t pin = {A,3,ALT};
	//init_pinX(pin);
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~3;
	GPIOA->MODER |= 2;//0b10 set pin 0 to ALT
	GPIOA->AFR[0] &= ~0xF;
	GPIOA->AFR[0] |= 0x1; // Setting AF1
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;//have tried APB2ENR
	//RCC->APB2ENR |= RCC_APB1ENR1_TIM2EN;//
	
	// Set prescalar
	TIM2->PSC = 80-1;
	TIM2->ARR = 0x4E20;//count of 20,000
	
	
	
	// Set CC1 to output mode bits 0b00 should be 0
	TIM2->CCMR1 &= ~3; // ensure previous values are clear
	

	
	// bit 4 to be 0 for upcount
	// bit 3 to be 0 for continuous
	TIM2->CR1 &= ~8;
	TIM2->CR1 &= ~4;

	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	// 
	TIM2->CCR1 = 2000;
	TIM2->EGR |= TIM_EGR_UG;
	
	
	// Clear bit 1 to set to active high
	TIM2->CCER &= ~2;
	

	
	// Start the clock
	TIM2->CR1 |= TIM_CR1_CEN;
}

//
// Checks to see if the flag has been set for TIM2 on chanel 1
int check_for_input(void){
	if((TIM2->SR & TIM_SR_CC1IF) != 0 )
		return 1;
	return 0;
}


