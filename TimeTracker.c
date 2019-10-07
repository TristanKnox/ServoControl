#include "TimeTracker.h"
#include "UI_Ginerics.h"


void start_clock(void);


// Create a new timer and set its initial time
// return timer
void init_timer(timer_t* timer, int timer_duration){
	timer->timer_active = 1;
	timer->initial_time = TIM3->CNT;
	timer->timer_duration = timer_duration;
}
//	TODO acount for clock overflow
// Calculate the time passed since init_timer
// return 1 if time is up
// return 0 if time is not up
int check_timer(timer_t* timer){
	int current_time = TIM3->CNT;
	int time_diff;
	if(current_time < timer->initial_time)
		time_diff = TIM_ARR_ARR - timer->initial_time + current_time;
	else
		time_diff = current_time - timer->initial_time; 
	
	
	if((time_diff >= timer->timer_duration) && timer->timer_active){
		timer->timer_active = 0;
		return 1;
	}
	return 0;
}

void init_timer_clock(void){
	start_clock();
}
void start_clock(){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	
	TIM3->PSC = (80-1) * 10000;
	TIM3->ARR = TIM_ARR_ARR;
	
	TIM3->CR1 &= ~TIM_CR1_DIR; //up_counting
	
	// Start the clock
	TIM3->CR1 |= TIM_CR1_CEN;
	
}

