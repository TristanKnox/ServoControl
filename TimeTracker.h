#include "stm32l476xx.h"

typedef struct{
	int initial_time;
	int timer_duration;
}timer_t;

timer_t init_timer(int timer_duration);
int check_timer(timer_t timer);
