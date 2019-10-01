#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PinSetup.h"
#include "ClockSetup.h"
#include "UI.h"

#include <string.h>
#include <stdio.h>
 
int post_routine(void);
	


int main(void){
	LED_Init();
	
	clock_setup();
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

