#include "stm32l476xx.h"

typedef struct{
	uint32_t initial_time;
	uint32_t timer_duration;
	int timer_active;
}timer_t;

void init_timer(timer_t* timer, int timer_duration);
int check_timer(timer_t* timer);
void init_timer_clock(void);
