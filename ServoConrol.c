#include "ServoControl.h"



// Helper Functions //
double getDutyCycle(servo_t* servo);
position_t get_position(int pos_number);
int get_current_pos_value(position_t pos);
int get_difference(int value_1, int value_2);
void set_servo_wait(servo_t* servo, command_t* command);

///////////////////////////////////////////
///////////////////////////////////////////

void init_servo(servo_t* servo, channel_t chan, int pwm_count){
	servo->channel = chan;
	servo->PWM_count = pwm_count;
	servo->state = READY_FOR_CMD;
	set_servo_position(servo,0);
}

void execute_CMD(servo_t* servo, command_t* command){
	if(command->opcode == MOV)
		set_servo_position(servo,command->value);
	if(command->opcode == WAIT)
		set_servo_wait(servo,command);
}

void set_servo_wait(servo_t* servo, command_t* command){
	servo->state = IS_WAITING;
	init_timer(&(servo->timer), command->value * SERVO_BASE_WAIT_TIME);
}

double get_puls_width(servo_t* servo){
	double duty_cycle = getDutyCycle(servo);
	return servo->PWM_count * (duty_cycle / 100);
}

void set_servo_position(servo_t* servo, int pos_number){
	int current_pos_value = get_current_pos_value(servo->pos);
	int positions_to_move = get_difference(pos_number, current_pos_value);
	servo->pos = get_position(pos_number);
	servo->state = IS_MOVING;
	set_puls_width(servo->channel,get_puls_width(servo));
	init_timer(&(servo->timer), SERVO_TIME_PER_POSITION*positions_to_move);
}

servo_state_t check_servo_state(servo_t* servo){
	if(servo->state ==  IS_MOVING || servo->state == IS_WAITING){ // If servo is in motion
		if(check_timer(&(servo->timer)))// And servo timer is complete
			servo->state = READY_FOR_CMD;
	}
	return servo->state;
}

void calibrate_servo(servo_t* servo, double max_duty, double min_duty){
	servo->max_duty_cycle = max_duty;
	servo->min_duty_cycle = min_duty;
}

double getDutyCycle(servo_t* servo){
	double pos_value = get_current_pos_value(servo->pos);
	double min = servo->min_duty_cycle;
	double max = servo->max_duty_cycle; 
	// the increment is the difference between each duty cycle
	double duty_cycle_increment = (max- min) / 5;
	return min + duty_cycle_increment * pos_value;
}

int get_difference(int value_1, int value_2){
	if( value_1 > value_2 )
		return value_1 - value_2;
	return value_2 - value_1;
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


	
