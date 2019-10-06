#include "TimeTracker.h"
#include "UI_Ginerics.h"

// Create a new timer and set its initial time
// return timer
timer_t init_timer(int timer_duration){
	timer_t timer;
	timer.initial_time = TIM2->CNT;
	timer.timer_duration = timer_duration;
	return timer;
}
//	TODO acount for clock overflow
// Calculate the time passed since init_timer
// return 1 if time is up
// return 0 if time is not up
int check_timer(timer_t timer){
	int current_time = TIM2->CNT;
	
	uint8_t buffer[1000];
	int msg = sprintf((char *) buffer, "%d\r\n",current_time);
	USART_Write(USART2,buffer,msg);
	
	if(current_time - timer.initial_time >= timer.timer_duration)
		return 1;
	return 0;
}

