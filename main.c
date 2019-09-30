#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PinSetup.h"
#include "ClockSetup.h"
#include "DataColector.h"
#include "UI.h"

#include <string.h>
#include <stdio.h>
 
int post_routine(void);
	


int main(void){
	
	// Initiat needed routiens
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	clockSetup();
	
	display_header(79,"Welcome to our Demo");
	
	int run = 1;
	// Run until the user specifies that they are done
	while(run){
		// Verify that there is data input
		while(!post_routine()){
			if(!try_again_promt("No input detected\r\nWould you like to run again? (Y/N)\r\n")){
				run = 0;
				break;
			}
		}
		// Break out of loop if user has specified that they no longer want to run
		if(!run)
			break;
		// Prompt for input, Gather data, display data
		prompt_for_limit();
		gather_data(1001);
		display_data();
		// Prompt user to run again
		if(!try_again_promt("Would you like to run again? (Y/N)"))
			run = 0;
	}
	display_string("Good bye");
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

