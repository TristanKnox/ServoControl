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
	
	pin_t PA0 = {A,0,ALT,AF1};
	init_pinX(PA0);
	set_ALT_function(PA0);
	
	pin_t PA3 = {A,3,ALT,AF1};
	init_pinX(PA3);
	set_ALT_function(PA3);
	
//	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
//	GPIOA->MODER &= ~3;
//	GPIOA->MODER |= 2;//0b10 set pin 0 to ALT
//	GPIOA->AFR[0] &= ~0xF;
//	GPIOA->AFR[0] |= 0x1; // Setting AF1
//	GPIOA->PUPDR &= ~3;	//CLEAR bits 0 and 1 to endure pin is set for no pull-up pull-down
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;//have tried APB2ENR
	//RCC->APB2ENR |= RCC_APB1ENR1_TIM2EN;//
	
	
	// Counting direction: 0 = Up-counting, 1 = Down-counting
	TIM2->CR1 &= ~TIM_CR1_DIR; //up_counting
	
	// Set prescalar
	TIM2->PSC = 80-1;
	TIM2->ARR = 2000;//999;//0x4E20;//count of 20,000
	
	
	// Clear output compare mode bits for channel 1
	// Set CC1 to output mode bits 0b00 should be 0
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;//~3; // ensure previous values are clear
	TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;
	
	// Select PWM Mode 1(OC1M = 110)
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // channel 1
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; // channel 4
	
	
	// Output 1 preload enable
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // channel 1
	TIM2->CCMR2 |= TIM_CCMR2_OC4PE; // channel 4
								 
	//Select output polarity: 0 = Activ high, 1 = Active low
	// Clear bit 1 to set to active high
	TIM2->CCER |= TIM_CCER_CC1E;//~2; // channel 1
	TIM2->CCER |= TIM_CCER_CC4E; // channel 4

	


// not sure it this is needed
//	// bit 4 to be 0 for upcount
//	// bit 3 to be 0 for continuous
	TIM2->CR1 &= ~8;
	TIM2->CR1 &= ~4;
	TIM2->CR1 |= TIM_CR1_ARPE; 

	
	// 
	TIM2->CCR1 = 100; // channel 1
	TIM2->CCR4 = 1000; // channel 4
	//TIM2->EGR |= TIM_EGR_UG;
	
	
	
	

	
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


