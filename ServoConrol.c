#include "ServoControl.h"



// Helper Functions //
double getDutyCycle(position_t pos);
position_t get_position(int pos_number);


void init_servo(servo_t* servo, channel_t chan, int pwm_count){
	servo->channel = chan;
	servo->PWM_count = pwm_count;
	set_servo_position(servo,0);
}

double get_puls_width(servo_t* servo){
	double duty_cycle = getDutyCycle(servo->pos);
	return servo->PWM_count * (duty_cycle / 100);
}

void set_servo_position(servo_t* servo, int pos_number){
	servo->pos = get_position(pos_number);
	set_puls_width(servo->channel,get_puls_width(servo));
}

double getDutyCycle(position_t pos){
	switch(pos){
		case POS0:
			return DUTY_CYCLE_0;
		case POS1:
			return DUTY_CYCLE_1;
		case POS2:
			return DUTY_CYCLE_2;
		case POS3:
			return DUTY_CYCLE_3;
		case POS4:
			return DUTY_CYCLE_4;
		case POS5:
			return DUTY_CYCLE_5;
		default:
			return DUTY_CYCLE_0;
	}
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


	
