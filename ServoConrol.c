#include "ServoControl.h"



// Helper Functions //
double getDutyCycle(servo_t* servo);
position_t get_position(int pos_number);
int get_current_pos_value(position_t pos);

///////////////////////////////////////////
///////////////////////////////////////////

void init_servo(servo_t* servo, channel_t chan, int pwm_count){
	servo->channel = chan;
	servo->PWM_count = pwm_count;
	servo->state = CAN_MOVE;
	set_servo_position(servo,0);
}

double get_puls_width(servo_t* servo){
	double duty_cycle = getDutyCycle(servo);
	return servo->PWM_count * (duty_cycle / 100);
}

void set_servo_position(servo_t* servo, int pos_number){
	int positions_to_move = get_current_pos_value(servo->pos);
	servo->pos = get_position(pos_number);
	servo->state = IS_MOVING;
	set_puls_width(servo->channel,get_puls_width(servo));
	init_timer(&servo->timer, SERVO_TIME_PER_POSITION*positions_to_move);
}

servo_state_t check_servo_state(servo_t* servo){
	if(servo->state ==  IS_MOVING){ // If servo is in motion
		if(check_timer(&servo->timer))// And servo timer is complete
			servo->state = CAN_MOVE;
	}
	return servo->state;
}

void calibrate_servo(servo_t* servo, int max_duty, int min_duty){
	servo->max_duty_cycle = max_duty;
	servo->min_duty_cycle = min_duty;
}

double getDutyCycle(servo_t* servo){
	int pos_value = get_current_pos_value(servo->pos);
	int min = servo->min_duty_cycle;
	int max = servo->max_duty_cycle; 
	// the increment is the difference between each duty cycle
	int duty_cycle_increment = (max- min) / 5;
	return min + duty_cycle_increment * pos_value;
}

position_t get_position(int pos_number){
	switch(pos_number){
		case 0:
			return POS0;
		case 1:
			return POS1;
		case 2:
			return POS2;
		case 3:
			return POS3;
		case 4:
			return POS4;
		case 5:
			return POS5;
		default:
			return POS0;
	}
}
int get_current_pos_value(position_t pos){
	switch(pos){
		case POS0:
			return 0;
		case POS1:
			return 1;
		case POS2:
			return 2;
		case POS3:
			return 3;
		case POS4:
			return 4;
		case POS5:
			return 5;
		default:
			return 0;
	}
}


	
