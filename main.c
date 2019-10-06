#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include "ClockSetup.h"
#include "UI.h"
#include "PWM.h"
#include "TimeTracker.h"

//#include "PinSetup.h"

#include <string.h>
#include <stdio.h>
 
int post_routine(void);
	
pin_t PA0 = {A,0,OUTPUT};
pin_t PA1 = {A,1,ALT,AF1};

int main(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	pin_t PA0 = {A,0,ALT,AF1};
	pin_t PA3 = {A,3,ALT,AF1};
	pin_t PA2 = {A,2,ALT,AF1};
	init_PWM(80*4,20000,CHAN1,MODE_1,PA0);
	add_output_channel(CHAN4,MODE_1,PA3);
	add_output_channel(CHAN3,MODE_1,PA2);
	
	set_puls_width(CHAN1,1000);
	set_puls_width(CHAN4,10000);
	set_puls_width(CHAN3,5000);
	
	//clock_setup();
	int duration = 6000;
	//Red_LED_On();
	timer_t timer;
	timer = init_timer(duration);
	int input_size = 20;
	char input[input_size];
	display_string("Starting");
	while(1){
		if(check_timer(timer)){
			Green_LED_On();
			Red_LED_Off();
			timer = init_timer(duration);
		}
		else{
			Green_LED_Off();
			Red_LED_On();
		}
		if(get_user_input(input,input_size)){
			display_string("Input Receved");
			display_string(input);
		}
	}
}

//
// Verify that board is receving data on the pin that was specified in clock setup (PAO)
int post_routine(void){
	display_charater_sequence(60,'-');
	display_string("Checking for input....");
	int start_time = TIM2->CNT;
	int time_limit = 100000;
	while((TIM2->CNT - start_time) < time_limit){
		if(check_for_input())
			return 1;
	}
	return 0;
		
}

