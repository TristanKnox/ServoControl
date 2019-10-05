#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include "ClockSetup.h"
#include "UI.h"
#include "PWM.h"
//#include "PinSetup.h"

#include <string.h>
#include <stdio.h>
 
int post_routine(void);
	
pin_t PA0 = {A,0,OUTPUT};
pin_t PA1 = {A,1,ALT,AF1};

int main(void){
	LED_Init();
	pin_t PA0 = {A,0,ALT,AF1};
	pin_t PA3 = {A,3,ALT,AF1};
	pin_t PA2 = {A,2,ALT,AF1};
	init_PWM(80,2000,CHAN1,MODE_1,PA0);
	add_output_channel(CHAN4,MODE_1,PA3);
	add_output_channel(CHAN3,MODE_1,PA2);
	
	set_channel_pulswidth(CHAN1,100);
	set_channel_pulswidth(CHAN4,1000);
	set_channel_pulswidth(CHAN3,500);
	//clock_setup();
	Red_LED_On();
	while(1){
		Green_LED_On();
		//for(int i = 0; i < 400000; i++);
		Green_LED_Off();
		//for(int i = 0; i < 400000; i++);
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

