#include "stm32l476xx.h"
# include "PinSetup.h"


typedef enum{
	MODE_1, MODE_2
}PWM_mode_t;

typedef enum{
	CHAN1, CHAN2, CHAN3, CHAN4
}channel_t;

void init_clock(void);
void init_PWM(int pre_scalar, int count, channel_t channel, PWM_mode_t mode, pin_t pin);
void set_output_pin(pin_t pin);
void enable_channel(channel_t channel, PWM_mode_t mode);
void set_PSC_and_count(int pre_scalar, int count);
void add_output_channel(channel_t channel, PWM_mode_t mode, pin_t pin);

void set_channel_pulswidth(channel_t channel, int count);

