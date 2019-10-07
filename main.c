#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "ServoControl.h"

#include "ClockSetup.h"
#include "UI.h"
//#include "PWM.h"
#include "TimeTracker.h"

//#include "PinSetup.h"

#include <string.h>
#include <stdio.h>
 
 
#define PCS 80
#define PWM_count 20000 
#define PWM_mode MODE_1


int post_routine(void);
	


int main(void){
	System_Clock_Init();
	LED_Init();
	init_timer_clock();
	UART2_Init();
	pin_t PA0 = {A,0,ALT,AF1};
	pin_t PA2 = {A,2,ALT,AF1};
	
	init_PWM(PCS,PWM_count);
	add_output_channel(CHAN1,PWM_mode,PA0);
	add_output_channel(CHAN3,PWM_mode,PA2);
	
	servo_t SERVO_1;
	servo_t SERVO_2;
		
	init_servo(&SERVO_1,CHAN1,PWM_count);
	init_servo(&SERVO_2,CHAN3,PWM_count);
		
	set_servo_position(&SERVO_2,5);
	set_servo_position(&SERVO_1,3);
	
	
	
	
	
	//clock_setup();
	int duration = 10000;
	//Red_LED_On();
	timer_t timer1;
	timer_t timer2;
	//init_timer(&timer2, 10000);
	init_timer(&timer1,duration);
	int input_size = 20;
	char input[input_size];
	display_string("Starting");
	while(1){
		if(check_timer(&timer1)){
			Green_LED_On();
			Red_LED_Off();
			init_timer(&timer2,duration);
		}
		else if(check_timer(&timer2)){
			Green_LED_Off();
			Red_LED_On();
			init_timer(&timer1,duration);
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

