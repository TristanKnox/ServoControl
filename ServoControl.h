#include "PWM.h"


// DUTY_CYCLE is the percentage of the PWM_cunt the output pin should be on 
#define DUTY_CYCLE_0 2.5
#define DUTY_CYCLE_1 3.6
#define DUTY_CYCLE_2 5.2
#define DUTY_CYCLE_3 6.8
#define DUTY_CYCLE_4 8.4
#define DUTY_CYCLE_5 10.0

// Represent the 6 positions the servo can be in
typedef enum{
	POS0,POS1,POS2,POS3,POS4,POS5
}position_t;


// Holds info each Servo needs to know
typedef struct{
	channel_t channel;
	position_t pos;
	int PWM_count;
}servo_t;


double get_puls_width(servo_t* servo);
void set_servo_position(servo_t* servo, int pos);
void init_servo(servo_t* servo, channel_t channel, int PWM_count);




