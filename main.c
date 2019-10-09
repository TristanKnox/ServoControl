#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"
#include "ServoControl.h"

#include "ClockSetup.h"
//#include "UI.h"
//#include "RecipeParser.h"
//#include "RecipeHandler.h"

#include <string.h>
#include <stdio.h>
 
 
#define PCS 80
#define PWM_count 20000 
#define PWM_mode MODE_1


// These values should be adjusted to calibrate each individual servo
// Once the min and max are set by using calibrat_servo the other duty cycles for positions in between are calculated as needed
#define SERVO_1_MIN_DUTY_CALIBRATION 3.1 //2.7  //Calibrated for box #13-2015 Right Servo
#define SERVO_1_MAX_DUTY_CALIBRATION 8.9 //9.2  //Calibrated for box #13-2015 Right Servo
#define SERVO_2_MIN_DUTY_CALIBRATION 2.7  //Calibrated for box #13-2015 Left Servo
#define SERVO_2_MAX_DUTY_CALIBRATION 9.8  //Calibrated for box #13-2015 Left Servo

#define START_POS 0

servo_t SERVO_1; //CHAN1,PA0
servo_t SERVO_2; //CHAN3,PA2


int post_routine(void);
void init_system_recources(void);	
void initial_PWM_setup(void);
void initial_servo_setup(void);

void update_servo_1(recipe_t* recipe_1);
void update_servo_2(recipe_t* recipe_2);

int main(void){

	init_system_recources();
	initial_PWM_setup();
	initial_servo_setup();
	
	
	
	int duration = 1000;
	timer_t loop_timer;
	init_timer(&loop_timer,duration);
	
	int input_size = 20;
	char input[input_size];
	display_string("Starting Main Loop");
	
	recipe_t recipe_1;
	recipe_t recipe_2;
	unsigned char recipe1[] = { LOOP + 2,MOV+ 5,MOV+0, END_LOOP,WAIT+ 5, LOOP + 5,MOV+5, WAIT+2,MOV+3,END_LOOP, RECIPE_END } ;
	unsigned char recipe2[] = { MOV | 5,WAIT+31,WAIT+31,WAIT+31,MOV+0, RECIPE_END, MOV + 5 } ;
	unsigned char demo_recipe[] = {MOV+0,MOV+5,MOV+0,MOV+3,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4,RECIPE_END};
	unsigned char recipe_loop_error[] = { LOOP + 2,MOV+ 5,MOV+0, LOOP+2,MOV+3,END_LOOP, END_LOOP, RECIPE_END } ;
	unsigned char recipe_error[] = {MOV+0,MOV+5,5,MOV+0,RECIPE_END};
	
	init_recipe(&recipe_1,recipe_loop_error);
	init_recipe(&recipe_2,recipe2);
	
	command_t servo1_command;
	command_t servo2_command;

	display_string("Starting Main Loop");
	while(1){
		if(check_timer(&loop_timer)){
			init_timer(&loop_timer,duration);
			
			update_servo_1(&recipe_1);
			update_servo_2(&recipe_2);
		}
		if(get_user_input(input,input_size)){
			display_string("Input Receved");
			display_string(input);
		}
	}
	
}

void init_system_recources(void){
	System_Clock_Init();
	LED_Init();
	init_timer_clock();
	UART2_Init();
}

void initial_PWM_setup(void){
	pin_t PA0 = {A,0,ALT,AF1};
	pin_t PA2 = {A,2,ALT,AF1};
	
	init_PWM(PCS,PWM_count);
	add_output_channel(CHAN1,PWM_mode,PA0);
	add_output_channel(CHAN3,PWM_mode,PA2);
}

void initial_servo_setup(void){
	init_servo(&SERVO_1,CHAN1,PWM_count);
	init_servo(&SERVO_2,CHAN3,PWM_count);
	calibrate_servo(&SERVO_1, SERVO_1_MAX_DUTY_CALIBRATION, SERVO_1_MIN_DUTY_CALIBRATION);
	calibrate_servo(&SERVO_2, SERVO_2_MAX_DUTY_CALIBRATION, SERVO_2_MIN_DUTY_CALIBRATION);
	
	set_servo_position(&SERVO_1,START_POS);
	set_servo_position(&SERVO_2,START_POS);
}

void update_servo_1(recipe_t* recipe_1){
	if(check_servo_state(&SERVO_1) == READY_FOR_CMD){
				if(recipe_1->is_active){
					Green_LED_On();
					command_t command = get_next_command(recipe_1);
					execute_CMD(&SERVO_1, &command);
				}
				else
					Green_LED_Off();
					
			}				
}

void update_servo_2(recipe_t* recipe_2){
	if(check_servo_state(&SERVO_2) == READY_FOR_CMD){
				if(recipe_2->is_active){
					command_t command = get_next_command(recipe_2);
					execute_CMD(&SERVO_2,&command);
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

