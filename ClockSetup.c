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
	TIM2->ARR = 0xFFFFFFFF;//How hight to count 
	
	TIM2->EGR |= TIM_EGR_UG;
	
	// Set the active input
	TIM2->CCMR1 &= ~3; // ensure previous values are clear
	TIM2->CCMR1 |= 1;  // 0b01: Channel 1 is set as input and mapped to timer input 1 (TI1)
	
	// Set input filter
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1F;	//CLEAR
	TIM2->CCMR1 |= TIM_CCMR1_IC1F; //	IC1F is 0010
	
	//Set the active Edge
	// CC1NP is bit 4
	//CC1P is bit 1
	// If CC1NP = 0 and CC1P = 0 then rising edges only
	// If CC1NP = 0 and CC1P = 1 then falling edges only
	// If CC1NP = 1 and CC1P = 1 then rising and falling edges 
	TIM2->CCER &= ~TIM_CCER_CC1P; //~8 clearing bit 4
	TIM2->CCER &= ~TIM_CCER_CC1NP; //~2 clearing bit 1
	
	// Set the input prescaler
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	
	// enable the input capture
	// by setting the CC1E regester which is bit 0
	TIM2->CCER |= 1;
	
	//Enable interrupt and DMA	
	TIM2->DIER |= TIM_DIER_CC1DE;
	TIM2->DIER |= TIM_DIER_CC1DE;
	
	// Start the clock
	TIM2->CR1 |= TIM_CR1_CEN;
	TIM2->SR &= ~1;
}

//
// Checks to see if the flag has been set for TIM2 on chanel 1
int check_for_input(void){
	if((TIM2->SR & TIM_SR_CC1IF) != 0 )
		return 1;
	return 0;
}


